#ifndef TASKLIST
#define TASKLIST

#include "stdio.h"
#include "task.h"
#include "structures/list.h"

typedef struct tasklist_t {
    List* list;
}Tasklist;


Tasklist* tasklist_new();
void tasklist_free(Tasklist *list);
void tasklist_destroy(Tasklist *list);

int tasklist_read(Tasklist *list, FILE* file);
int tasklist_dump(Tasklist *list, FILE* file);

Task* tasklist_get(Tasklist* list, int index);
Task* tasklist_remove(Tasklist* list, int index);

int tasklist_append(Tasklist *list, Task *task);

Tasklist* tasklist_search(Tasklist *list, char *string);

Tasklist* tasklist_merge(Tasklist *list, Tasklist *other);
int tasklist_display(Tasklist *list);

#endif
