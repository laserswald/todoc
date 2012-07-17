
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tasklist.h"

struct tasklist_t* tasklist_new(){
    struct tasklist_t* this = (struct tasklist_t*)malloc(sizeof(struct tasklist_t));
    this->task = NULL;
    this->next = NULL;
    return this;
}

void tasklist_free(struct tasklist_t* list){
    free(list->task);
    tasklist_free(list->next); 
}

int tasklist_append(struct tasklist_t* this, Task* t){
    if (this == NULL){
        // Make sure it's heard.
    }
    struct tasklist_t* index = this;

}
