#ifndef TASKLIST
#define TASKLIST

#include "task.h"

typedef struct tasklist_t {
    struct tasklist_t *next;
    Task *task;
}Tasklist;


Tasklist* tasklist_new();
void tasklist_free(Tasklist *list);

int tasklist_read(Tasklist *list, char* filename);
int tasklist_dump(Tasklist *list, char* filename);

Task* tasklist_get(Tasklist* list, int index);
Tasklist* tasklist_remove(Tasklist* list, int index);

int tasklist_append(Tasklist *list, Task *task);

Tasklist* tasklist_search(Tasklist *list, char *string);

Tasklist* tasklist_merge(Tasklist *list, Tasklist *other);
int tasklist_display(Tasklist *list);

#endif
