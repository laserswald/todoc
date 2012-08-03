
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

int tasklist_append(struct tasklist_t* this, struct task_t* t){
    if (this == NULL){
        // Make sure it's heard.
    }
    struct tasklist_t* index = this;
    //Probably sure we can move this to another function.

    while (index->task != NULL && index != NULL){
        index = index->next;
    }
    if (!index){
        struct tasklist_t* new = tasklist_new();
        new->task = t;
        index->next = new;
    } else {
        index->task = t;
    }
    return 0;
}

struct tasklist_t* tasklist_filter(struct tasklist_t* list, char* filter){
    if (!list || !list->task && !list->next){
        puts("Empty tasklist.")
        return NULL;
    }
}

void tasklist_dump(struct tasklist_t *list, char* filename)
{
    FILE* f = fopen(filename, "w");
    if (f == NULL){
        puts("Could not open file for tasklist writing.");
        return;
    }
    struct tasklist_t *iter = list;
    while (iter != NULL){
        fprintf(f, "%s\n", iter->task->description);
        iter = iter->next;
    }
    fclose(f);
    return;
}

void tasklist_read(struct tasklist_t *list, char* filename){
    FILE* f = fopen(filename, "w");
    if (f == NULL){
        puts("Could not open file for tasklist writing.");
        return;
    }
    struct tasklist_t* iter = list;
    
    // Moves the index to the end.
    while (iter->next){
        iter = iter->next;
    }    
    char buffer[256];
    while (fgets(buffer, 255, f) != NULL){
        struct tasklist_t* new = tasklist_new();
        new->task = task_new();
        task_append(new->task, buffer);
        iter->next = new;
        iter = iter->next;
    }
}
