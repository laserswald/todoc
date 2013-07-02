#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#include "task.h"


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
    returnString[0] == '\0';
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
void task_parse(Task* task, char* string){
    char* restOfString = malloc(256); 
    // Get the completion status.
    if(sscanf(string, "x %s", restOfString) != EOF){
        task->complete = true;
    } else {
        task->complete = false;
        restOfString = string;
    }
    string = restOfString;
    int c = -1;
    if (sscanf(string, "(%c) %s", c, restOfString)){
        
    }
    free(restOfString);
}

// Returns true if the search finds something; false otherwise.
bool task_has_keyword(Task* t, char* keyword){
	if (strstr(t->description, keyword) == NULL){
		return false;
	} else {
	    return true;
    }
}
