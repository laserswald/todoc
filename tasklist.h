#ifndef TASKLIST
#define TASKLIST

#include <stdio.h>
#include "task.h"
#include "dllist.h"

typedef struct tasklist {
    // This trick allows all of dllist's methods to work on Tasklist. Hell yeah.
    union {
        struct dllist;
        dllist list;
    };
} tasklist;

/// Create a new tasklist.
//  This function malloc's a tasklist from memory.
tasklist* tasklist_new();

/// Frees a tasklist from memory. 
//  This does NOT delete the tasks. See tasklist_destroy for that.
void tasklist_free(tasklist *list);

/// Destroys a tasklist with all the tasks.
void tasklist_destroy(tasklist *list);

/// Reads a todo.txt file and populates a tasklist with it
int tasklist_read(tasklist *list, FILE* file);

/// Dumps a tasklist to a file
int tasklist_dump(tasklist *list, FILE* file);

Task *tasklist_get(tasklist *list, int index);
Task *tasklist_remove(tasklist *list, int index);

tasklist* tasklist_search(tasklist *list, char *string);

int tasklist_display(tasklist *list);

#endif
