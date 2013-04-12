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
}Task;

Task* task_new();
void task_free(Task* task);
void task_set_string(Task* t, char* string);

int task_append(Task* t, char* string);

void task_complete(Task* task);

bool task_has_keyword(Task* t, char* string);

void task_parse(Task* t, char* string);

int task_has_project(Task* t, char* project);
int task_has_context(Task* t, char* context);

char* task_dump(Task* t);

void task_print(Task* t);
#endif
