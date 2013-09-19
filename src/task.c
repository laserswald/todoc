#include <math.h> //for parsedate()
#include <regex.h> //gnu's regex.h
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <task.h>  //from libstr library

#include "str.h"

// Make a new task. 
Task* task_new(){
    Task* t = (Task*)malloc(sizeof(Task));

    // Set the description to a newly allocated space in memory with nothing in it.
	t->description = strdup("");
    t->priority = ' ';
    t->complete = false;
	return t;
}

/** Frees a task from memory, deleting it.
 *
 */
void task_free(Task* task){
    free(task->description);
    free(task);
}

/** Set the task's description to the given string.
 * This function simply duplicates the given string 
 * to a new section in memory and sets the task's 
 * description to it.
 *
 * @param t The task to manipulate
 * @param string The string to set the description to.
 */
void task_set_string(Task* t, char* string){
    t->description = strdup(string);
}

/** Append text to a task.
 * This function adds the string given to the task's description.
 * 
 * @param t The task to edit.
 * @param string The string to append.
 *
 * @return 0 if there was no error; 1 if there is.
 */
int task_append(Task* t, char* string){

    // If it's a null, return true, there's an error.
	if (t == NULL) return 1;     
	int oldlen, newlen;
    
    // Get the length of the string before and after. 
    oldlen = strlen(t->description);
	newlen = strlen(string) + oldlen + 1;

    // Reallocate the string's space in memory and concatenate the given string.
	t->description = realloc(t->description, (sizeof(char) * newlen));
	strncat(t->description, string, newlen);
    
    // No error, so return false.
    return 0;
}

// Get the priority of this task.
char get_priority(Task* task){
    char ch = task->priority;
    return ch;
}

// Set the completion status of this task.
void task_complete(Task* task){
    task->complete = true;
}

/** Dumps out the current task's data in Todo.txt format.*/
char* task_dump(Task* t){
	// Sanity checks.
    if (t == NULL) return NULL;
    if (t->description == NULL) return NULL;
    if (strcmp(t->description, "") == 0) return NULL;
    
    // Allocate a string of size 1 to add onto.
    char* returnString = (char*)malloc(sizeof(char)* 1);
    if (returnString == NULL){
        puts("Could not allocate space for task dump string.");
        return NULL;
    }
    int strLength = 0;

    // Build each part of the task.

    // Build the completion part
    if (t->complete){
        strLength += 2;
        returnString = realloc(returnString, strLength+1);
        strcat(returnString, "x ");
    }
    
    // Add the description.
    strLength += strlen(t->description);
    returnString = realloc(returnString, strLength);    
    if (returnString == NULL){
        perror("Cannot dump task");
        free(returnString);
        return NULL;
    }
    returnString = strcat(returnString, t->description);

    // return the string.
	return returnString;
}

// FIXME: This is not complete or even working.
/*
 * void task_parse(Task* task, char* string){
 *     char* restOfString = malloc(256); 
 *     // Get the completion status.
 *     if(sscanf(string, "x %s", restOfString) != EOF){
 *         task->complete = true;
 *     } else {
 *         task->complete = false;
 *         restOfString = string;
 *     }
 *     string = restOfString;
 *     char* c = NULL;
 *     if (sscanf(string, "(%c) %s", c, restOfString)){
 *         
 *     }
 *     free(restOfString);
 * }
 *  */

//helper function for task_parse
//converts from form "YYYY-MM-DD" to DDMMYYYY as an int 
int parsedate(char* expr){
	int stamp = 0;
	//because this function will only be called when expr is in correct
	//format we don't need to do any checking 

	//pull out the characters in form DDMMYYYY form
	char tmpform[9];
	strsub(expr,8,9,tmpform);
	strsub(expr,5,6,tmpform+2);
	strsub(expr,0,3,tmpform+4);
	tmpform[8] = '\0';

	size_t i;
	//the "-48" is to convert from ascii to int
	for (i = 0; i < 8; i++)
		stamp += (tmpform[7-i]-48)*pow(10,i);
	return stamp;
}

Task* task_parse(Task* task, char* str){
	//define variables
	size_t nmatches; //number of regex substrings
	regex_t regexpr; //struct to hold compiled regex (man regex.h)
	char buff[1000]; //a large buffer to use with str.sub
	size_t descstrt = 0; //holds the index of the start of the description, default: beginning of 0
	
	//regex string for parsing 
	//       complete?>|priority?_--->|date?-------______---------------->|desc----->|
	char* regx = "^(x )?(\\([A-Z]\\) )?([0-9]{4,4}-[0-9]{2,2}-[0-9]{2,2} )?([^\n]*)$";

	//compile the regex struct
	VALIDEXPR(!regcomp(&regexpr,regx,REG_EXTENDED),NULL);
	nmatches = regexpr.re_nsub;
	regmatch_t matches[nmatches];

	//execute the regex tree
	VALIDEXPR(!regexec(&regexpr,str,nmatches,matches,0),NULL);

	//grab the data matched and store it in the Task
	size_t i;
	for (i = 1; i < nmatches; i++)
	{
		//for each valid index grab info from matches[]
		//depending on i map info grabbed and assign to task
		/* map
 		 * 1 - complete?
 		 * 2 - priority?
 		 * 3 - date? 
 		 */
		int strt = matches[i].rm_so;
		int end  = matches[i].rm_eo;
		if(strt == -1 || end == -1) continue;
	
		descstrt = end;	
		switch(i)
		{
			case 1: 
				task->complete = true;
				break;
			case 2: 
				task->priority = *(str+strt+1);
				break;
			case 3: 
				task->datestamp = parsedate(strsub(str,strt,end,buff));
				break;
		}
	}

	//get the description which starts from the last valid end index
	strsub(str,descstrt,strlen(str)-1,buff);
	char* desc = (char*)malloc(sizeof(char)*strlen(buff));
	strncpy(desc,buff,strlen(buff));
	task->description = desc;

	return task;
}

// Returns true if the search finds something; false otherwise.
bool task_has_keyword(Task* t, char* keyword){
	if (strstr(t->description, keyword) == NULL){
		return false;
	} else {
	    return true;
    }
}
