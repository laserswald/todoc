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
    task_clear(t);
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
    else asprintf(&(t->description), "%s%s", t->description, string);  
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

//converts from form "YYYY-MM-DD" to DDMMYYYY as an int 
date* parsedate(char* expr){
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

static bool extract_complete(bstring taskstr){
    if (taskstr->data[0] == 'x')
        return true;
    else return false;
}

static bstring remove_part(bool b, bstring s, size_t len){
    bstring ret;
    if (b){
        ret = bmidstr(s, len, s->slen);
    } else ret = s;
    return ret;
}

//Parse a string into a Task.
int task_parse(Task* task, char* str){
	//sanity checks
    check(task, "Task was not given.");
    check(str, "String is null.");

    bstring s = bfromcstr(str);

    task->complete = extract_complete(s);
    s = remove_part(task->complete, s, 2);

    if (isdigit(s->data[0])){
        bstring datestr = bmidstr(s, 0, 11);
        task->date_started = parsedate(bstr2cstr(datestr, ' '));
        s = remove_part(true, s, 11);
    }

    task->priority = extract_priority(s);  
    bool x = (task->priority != '\0');
    s = remove_part(x, s, 4);
    
    task->description = bstr2cstr(s, ' ');  
    bdestroy(s);
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
    t->linenumber = 0;
	// Set the description to a newly allocated space in memory with nothing in it.
	t->description = NULL;
	t->priority = ' ';
	t->complete = false;
	t->date_started = NULL;
    t->date_completed = NULL;
}
