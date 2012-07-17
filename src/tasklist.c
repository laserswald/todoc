#include "tasklist.h"

TaskList* TaskList_new(){
    TaskList* this = (TaskList*)malloc(sizeof(TaskList));
    this->task = NULL;
    this->next = NULL;
    return this;
}

void TaskList_free(TaskList* list){
    free(list->task);
    TaskList_free(list->next); 
}

int TaskList_append(TaskList* this, Task* t){
    if (this == NULL){
        // Make sure it's heard.
    }
}
