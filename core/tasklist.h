#ifndef TASKLIST
#define TASKLIST

#include "stdio.h"
#include "task.h"
#include "structures/list.h"

typedef struct tasklist_t {
    List* list;
}Tasklist;

/// Create a new tasklist.
//  This function malloc's a tasklist from memory.
Tasklist* tasklist_new();

/// Frees a tasklist from memory. 
//  This does NOT delete the tasks. See tasklist_destroy for that.
void tasklist_free(Tasklist *list);

/// Destroys a tasklist with all the tasks.
void tasklist_destroy(Tasklist *list);

/// Reads a todo.txt file and populates a tasklist with it
int tasklist_read(Tasklist *list, FILE* file);

/// Dumps a tasklist to a file
int tasklist_dump(Tasklist *list, FILE* file);

Task* tasklist_get(Tasklist* list, int index);
Task* tasklist_remove(Tasklist* list, int index);

int tasklist_append(Tasklist *list, Task *task);

Tasklist* tasklist_search(Tasklist *list, char *string);

Tasklist* tasklist_merge(Tasklist *list, Tasklist *other);
int tasklist_display(Tasklist *list);

#endif
