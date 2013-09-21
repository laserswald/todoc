#include <stdbool.h>

/*  task.h
 *  
 *  A task structure and accompanying functions.
 */
#ifndef TASK
#define TASK

typedef struct task_t{
	char* description;
	char priority;
  bool complete;
	int datestamp; //added this so we can sort tasks by due date if needed, not to mention the due
								 //date is part of the task standard
}Task;

Task* task_new();
void task_free(Task* task);
void task_set_string(Task* t, char* string);

int task_append(Task* t, char* string);

void task_complete(Task* task);

bool task_has_keyword(Task* t, char* string);

/*
 * FUNCTION: task_parse
 * 
 * DESCRIPTION: parses the given string, inserting the info into the given task
 *
 * PARAMETERS: Task* task, char* str
 *
 * RETURNS: Task* - task with inserted data. Returns NULL if error occurs. An invalidly formatted
 * task will not trigger an error. Instead the entire task is treated as the description of the
 * task.
 *
 * AUTHOR: theNerd247
 * 
 * NOTE: this function calls malloc to set task->description.
 *
 */
Task* task_parse(Task* task, char* str);

int task_has_project(Task* t, char* project);
int task_has_context(Task* t, char* context);

char* task_dump(Task* t);

void task_print(Task* t);
#endif
