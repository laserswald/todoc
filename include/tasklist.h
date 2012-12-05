#ifndef TASKLIST
#define TASKLIST

#include "task.h"

struct tasklist_t {
    struct tasklist_t *next;
    struct task_t *task;
};


struct tasklist_t* tasklist_new();
void tasklist_free(struct tasklist_t *list);

int tasklist_read(struct tasklist_t *list, char* filename);
int tasklist_dump(struct tasklist_t *list, char* filename);

struct task_t* tasklist_get(struct tasklist_t* list, int index);
struct tasklist_t* tasklist_remove(struct tasklist_t* list, int index);

int tasklist_append(struct tasklist_t *list, struct task_t *task);

struct tasklist_t* tasklist_search(struct tasklist_t *list, char *string);

struct tasklist_t* tasklist_merge(struct tasklist_t *list, struct tasklist_t *other);
int tasklist_display(struct tasklist_t *list);

#endif
