#include <stdbool.h>

/*  task.h
 *  
 *  A task structure and accompanying functions.
 */
#ifndef TASK
#define TASK

struct task_t{
	char* description;
	char priority;
    bool complete;    
};

struct task_t* task_new();
void task_free(struct task_t* task);
void task_set_string(struct task_t* t, char* string);

int task_append(struct task_t* t, char* string);

void task_complete(struct task_t* task);

int task_has_keyword(struct task_t* t, char* string);

void task_parse(struct task_t* t, char* string);

int task_has_project(struct task_t* t, char* project);
int task_has_context(struct task_t* t, char* context);

const char* task_dump(struct task_t* t);

void task_print(struct task_t* t);
#endif
