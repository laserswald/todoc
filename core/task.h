
/*  task.h
 *  
 *  A task structure and accompanying functions.
 */
#ifndef TASK
#define TASK

#include "date.h"
#include <stdbool.h>

/** A structure storing information about tasks. */
typedef struct task_t{
    int linenumber; /** The line number in the file. */
	char* description; /**< description of what the task is about. */
	char priority; /**< priority of the task. */
    bool complete; /**< completion status */
	date* datestamp; /**< completion date */ 
}Task;

/** Allocate a new Task.
 *
 * \return A new Task instance.
 */
Task* task_new();

/** Free a task.
 *
 * Deletes the task, returning the memory to the heap.
 *
 * \param task The task to free.
 */
void task_free(Task* task);

/** Set the task's description to the given string.
 * 
 * This function simply duplicates the given string 
 * to a new section in memory and sets the task's 
 * description to it.
 *
 * \param t The task to manipulate
 * \param string The string to set the description to.
 */
void task_set_string(Task* t, const char* string);

/** Append text to a task.
 * 
 * This function adds the string given to the task's description.
 * 
 * \param t The task to edit.
 * \param string The string to append.
 *
 * \return 0 if there was no error; 1 if there is.
 */
int task_append(Task* t, const char* string);

/** Set the completion status of the task.
 */
void task_set_complete(Task* task, bool status);

void task_set_lineno(Task* task, int lineno);

/** Search if the task has a keyword in the description.
 */
bool task_has_keyword(Task* t, const char* string);

/** Parse the given string, inserting the info into the given task
 * 
 * \param task The task to update. 
 * \param str The string to parse.
 *
 * \return 0 if everything is okay, a negative number if an error occurs.
 *
 * \author Noah Harvey 
 */
int task_parse(Task* task, char* str);

/** Checks if the task has the given project.
 *  
 *  This function is equivalent to using task_has_keyword with the 
 *  string starting with + and the name of the project.
 *
 * \param t The task to search.
 * \param project The project to test for. 
 */ 
int task_has_project(Task* t, char* project);


int task_has_context(Task* t, char* context);

char* task_dump(Task* t);

void task_show(Task* t);

// Compares the tasks together. 
int task_default_compare(void* a, void* b);

#endif
