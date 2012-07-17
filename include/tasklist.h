#ifndef TaskList
#define TaskList

#include "task.h"

typedef struct tasklist_t {
    TaskList *next;
    Task* this;
}TaskList;

TaskList* TaskList_new();
void TaskList_delete(TaskList *list);

int TaskList_append(TaskList *list, Task *task);
TaskList* TaskList_filter(TaskList *list, char *string);

TaskList* TaskList_merge(TaskList *list, TaskList *other);
void TaskList_display(TaskList *list)

#endif
