#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#include "task.h"

struct task_t* task_new(){
	// Allocate a new task.
    struct task_t* t = (struct task_t*)malloc(sizeof(struct task_t));

    // Set the description to a newly allocated space in memory with nothing in it.
	t->description = strdup("");
    t->priority = ' ';
    t->complete = false;
	return t;
}

void task_set_string(struct task_t* t, char* string){
    t->description = strdup(string);
}

/** Append text to a task. 
 *  This function reallocates the description 
 */
int task_append(struct task_t* t, char* string){

    // If it's a null, return true, there's an error.
	if (t == NULL) return 1;     
	int oldlen, newlen;
	
    oldlen = strlen(t->description);
	newlen = strlen(string) + oldlen;
	t->description = realloc(t->description, (sizeof(char)*newlen)+1);
	strcat(t->description, string);
    
    // No error, so return false.
    return 0;
}

char get_priority(struct task_t* task){
    char ch = task->priority;
    return ch;
}

void task_complete(struct task_t* task){
    task->complete = true;
}

/** Dumps out the current task's data in Todo.txt format.*/
/* WARNING: Unclean code! */
const char* task_dump(struct task_t* t){
	// Error checking.
    if (t == NULL) return "";
    if (t->description == NULL) return "";
    if (strcmp(t->description, "") == 0) return "";

    char* returnString = (char*)malloc(sizeof(char)* 1);
    int strLength = 0;
    // Build each part of the task
    

    if (t->complete){
        strLength += 2;
        returnString = realloc(returnString, strLength+1);
        strcat(returnString, "x ");
    }
    
    strLength += strlen(t->description);
    returnString = realloc(returnString, strLength);    
    strcat(returnString, t->description);

	return returnString;
}

int task_has_keyword(struct task_t* t, char* keyword){
	if (strstr(t->description, keyword) == NULL){
		return 0;
	} else {
	    return 1;
    }
}
