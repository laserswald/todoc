#ifndef TASKLIST
#define TASKLIST

#include "task.h"

struct tasklist_t {
    struct tasklist_t *next;
    struct task_t *task;
};


struct tasklist_t* tasklist_new();
void tasklist_free(struct tasklist_t *list);

int tasklist_append(struct tasklist_t *list, Task *task);
struct tasklist_t* tasklist_filter(struct tasklist_t *list, char *string);

struct tasklist_t* tasklist_merge(struct tasklist_t *list, struct tasklist_t *other);
void tasklist_display(struct tasklist_t *list);

#endif
