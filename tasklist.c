/* Tasklist.c
 * Methods that perform operations on tasklists.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "task.h"
#include "tasklist.h"
#include "dbg.h"

// Make a new tasklist.
tasklist* tasklist_new(){
    tasklist* this = (tasklist*)malloc(sizeof(tasklist));
    dllist_init(&(this->list));
    return this;
}

void destroytask(void* item){
    Task* t = (Task*)item;
    task_free(t);    
}

// Destroy the given tasklist.
void tasklist_destroy(tasklist* list){
    if (list == NULL) return;
    dllist_do(&(list->list), &destroytask);
    tasklist_free(list);
}

void tasklist_free(tasklist* list){
    dllist_free(&(list->list));
    free(list);
}

// Construct a tasklist of tasks that match the filter.
tasklist* tasklist_search(tasklist* list, char* filter){

    bool filterfunc(void* v){
				Task* tmptsk = (Task*)v;
				char* str = (char*)tmptsk->description;
        if (strstr(str, filter) != NULL) return true;
        else return false;
    }
    
    dllist* matches = dllist_filter(&(list->list), *filterfunc);
    tasklist* t = tasklist_new();
    t->list = *matches;
    return t;
}

// Print out a Tasklist to the console.
int tasklist_display(tasklist* list){
    dllist* sorted = dllist_sort(&(list->list), &task_default_compare);
    int count = 0;
    void print_task(void* item){
        Task* t = (Task*)item;
        task_show(t);
        count ++;
    }
    dllist_do(sorted, &print_task);
    return count;
}

// Write a tasklist to a file.
int tasklist_dump(tasklist *list, FILE* f){
    void d(void* item){
        Task* t = (Task*)item;
        fprintf(f, "%s\n", task_dump(t));
    }
    dllist_do(&(list->list), &d);
    return 0;
}

// Read a tasklist from a file.
int tasklist_read(tasklist *list, FILE* f){
    check(list, "Task list does not exist.");
    check(f, "Something wrong happened with the file.");

    // Go through the file one line at a time.
    char buffer[256];
    int lineno = 0;
    while (fgets(buffer, 255, f) != NULL){
        lineno ++; 
        // Remove the ending newline.
        char* start = buffer;
        int newline = strcspn(buffer, "\n");
        start[newline] = '\0';

        // Make a task to hold the line.
        Task* temp = task_new();
        task_set_lineno(temp, lineno);
        task_parse(temp, buffer);

        // Add it to the list.
        dllist_append(&(list->list), temp);
    }

    return 0;

error:
    return -1;
}

Task* tasklist_get(tasklist* this, int index){
    struct dlnode* node = dlnode_seek(this->list.head, index);
    return (Task*)node->data;
}

Task* tasklist_remove(tasklist* this, int index){
    struct dlnode* node = dlnode_seek(this->list.head, index);
    Task* t = node->data;
    if(this->list.head == node) this->list.head = node->next;
    if(this->list.tail == node) this->list.tail = node->prev;
    dlnode_unlink(node);
    dlnode_free(node);
    return t;
}
