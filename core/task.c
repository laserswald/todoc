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

#include "util/dbg.h"
//#include "str.h"  //from libstr library
#include "bstrlib/bstrlib.h"
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
    bcstrfree(task->description);
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

static char extract_priority(bstring taskstr){
    bstring prio = bmidstr(taskstr, 0, 4);
    if (prio->data[0] == '(' && 
        prio->data[2] == ')' &&
        prio->data[3] == ' ' &&
        isupper(prio->data[1])){ 
        return prio->data[1];
    } else {
        return '\0';
    }
    bdestroy(prio);
}

//Parse a string into a Task.
int task_parse(Task* task, char* str){
	//sanity checks
    check(task, "Task was not given.");
    check(str, "String is null.");

    bstring s = bfromcstr(str);
    bstring desc; 
     
    char p = extract_priority(s);  
    // Check and make sure the priority is the correct format.
    if (p != '\0'){
        desc = bmidstr(s, 4, s->slen);
    } else {
        desc = s;
    }
    task->priority = p;
     
    task->description = bstr2cstr(desc, ' ');  
    bdestroy(s);
    bdestroy(desc);
    return 0;

error:
    return 1;
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

void task_clear(Task* t){
    t->description = NULL;
    t->priority = '\0';
}
