#define _GNU_SOURCE // For asprintf()

#include <math.h> //for parsedate(), task_dump()
#include <regex.h> //gnu's regex.h
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h> //for parsedate()
#include <regex.h> //gnu's regex.h

#include "dbg.h"
#include "str.h"  //from libstr library
#include "date.h"
#include "task.h"  

// Make a new task. 
Task* task_new(){
	Task* t = (Task*)malloc(sizeof(Task));
    t->linenumber = 0;
	// Set the description to a newly allocated space in memory with nothing in it.
	t->description = strdup("");
	t->priority = ' ';
	t->complete = false;
	t->datestamp = NULL;
	return t;
}

// Free a task.
void task_free(Task* task){
    free(task->description);
    free(task);
}

// Set the task's string to the string given.
void task_set_string(Task* t, const char* string){
    t->description = strdup(string);
}

// Appends the string to the task.
int task_append(Task* t, const char* string){
    // If it's a null, return true, there's an error.
	if (t == NULL) return 1;
    if (!t->description) t->description = strdup(string);    
    asprintf(&(t->description), "%s%s", t->description, string);  
    // No error, so return false.
    return 0;
}

// Get the priority of this task.
char get_priority(Task* task){
    char ch = task->priority;
    return ch;
}

// Set the completion status of this task.
void task_set_complete(Task* task, bool status){
    task->complete = status;
}

void task_set_lineno(Task* task, int lineno){ task->linenumber = lineno; }
void task_show(Task* t){
    char* dumped = task_dump(t);
    printf("%d: %s\n", t->linenumber, dumped);
}

/** Dumps out the current task's data in Todo.txt format.*/
char* task_dump(Task* t){
	// Sanity checks.
    if (t == NULL) return NULL;
    if (t->description == NULL) return NULL;
    if (strcmp(t->description, "") == 0) return NULL;
    
    char* returnString;
    int err = asprintf(&returnString, "%s", t->description);
    check(err != 0, "Asprintf cannot load description of task");  

    // Build the completion part
    if (t->complete){
        // TODO: Add the completion date.  
        //char* date =  get_date();
        check(asprintf(&returnString, "x %s", returnString) != -1, "Asprintf died.");      
    } 
    
   // return the string.
	return returnString;
error:
    free(returnString);
    return NULL;
}

// TODO: Make this make more sense and move it to another file
//converts from form "YYYY-MM-DD" to DDMMYYYY as an int 
date* parsedate(char* expr){
	//pull out the characters in form DDMMYYYY form
    
    /* OLD CODE
	char tmpform[9];
	strsub(expr,8,9,tmpform);
	strsub(expr,5,6,tmpform+2);
	strsub(expr,0,3,tmpform+4);
	tmpform[8] = '\0';
	//the "-48" is to convert from ascii to int
	return atoi(tmpform);
    */
    int year = 0;
    int month = 0;
    int day = 0;
    sscanf(expr, "%d-%d-%d", &year, &month, &day);
    date* d = date_new(year, month, day);
    return d;
}

//Parse a string into a Task.
int task_parse(Task* task, char* str){
	//sanity checks
	if(!task || !str) return -1;	
	if(strcmp(str,"") == 0) return -1;

	//define variables
	size_t nmatches; ///<number of regex substrings
	regex_t regexpr; // struct to hold compiled regex (man regex.h)
	char buff[11]; // a large buffer to use with str.sub
	size_t descstrt = 0; //holds the index of the start of the description, default: beginning of 0
	
	//regex string for parsing 
	//       complete?>|priority?_--->|date?-------______---------------->|desc----->|
	char* regx = "^(x )?(\\([A-Z]\\) )?([0-9]{4,4}-[0-9]{2,2}-[0-9]{2,2} )?([^\n]*)$";

	//compile the regex struct
	int compstat = regcomp(&regexpr,regx,REG_EXTENDED);
    check(compstat == 0, "Regex could not compile: status is %d", compstat);
	nmatches = regexpr.re_nsub;

	regmatch_t *matches = calloc(sizeof(regmatch_t), nmatches);

	//execute the regex tree
	check(regexec(&regexpr,str,nmatches,matches,0) != REG_NOMATCH, "Regex did not match this string.");

	//grab the data matched and store it in the Task
	int i;
	for (i = 1; i < nmatches; i++)
	{
		//for each valid index grab substring using the index given by matches[]
		/* map i =
 		 * 1 - complete?
 		 * 2 - priority?
 		 * 3 - date? 
 		 */
		int strt = matches[i].rm_so;
		int end  = matches[i].rm_eo;
		if(strt == -1 || end == -1) continue;
	
		//depending on i set the values of the task
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
    
    free(matches);

    //get the description which starts from the last valid end index
	char* desc = malloc(sizeof(char)*(strlen(str)-descstrt+1));
	strsub(str,descstrt,strlen(str)-1,desc);

	if (task->description) free(task->description); //get rid of the old description if it exists
	task->description = desc;

	return 0;

error:
    free(matches);
    return -1;
}

// Returns true if the search finds something; false otherwise.
bool task_has_keyword(Task* t, const char* keyword){
	if (strstr(t->description, keyword) == NULL){
		return false;
	} else {
	    return true;
    }
}

int compare_completion(Task* a, Task* b){
    if (a->complete && !b->complete) return 1;
    if (!a->complete && b->complete) return -1;
    return 0; 
}

int task_default_compare(void* a, void* b){
    Task* ta = a;
    Task* tb = b;
    // Move all the complete tasks to the bottom.
    int complete = compare_completion(a,b); 
    if (complete != 0) return complete;
    
    return strcmp(ta->description, tb->description);  
}
