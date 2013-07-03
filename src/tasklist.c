/* tasklist.c
 * Methods that perform operations on tasklists.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "task.h"
#include "tasklist.h"

// Make a new tasklist.
Tasklist* tasklist_new(){
    Tasklist* this = (Tasklist*)malloc(sizeof(Tasklist));
    this->list = new_llist();
    return this;
}

// Destroy the given tasklist.
void tasklist_free(Tasklist* list){
    if (list == NULL) return;
    destroy_llist(list->list);
}

// Add a new task to the end of this list.
int tasklist_append(Tasklist* this, Task* t){
    if (this == NULL){
        // Make sure it's heard.
        return 1;
    }
    lladd(this->list, t);
    return 0;
}

// Get the task at the index.
Task* tasklist_get(Tasklist* list, int index){
    Task* t = (Task*)llget(list->list, index);
    return t;
}

// Remove the task at the index.
Task* tasklist_remove(Tasklist* list, int index){
    return ( (Task*)llrem(list->list, index) );
}


// Construct a tasklist of tasks that match the filter.
Tasklist* tasklist_search(Tasklist* list, char* filter){

    bool filterfunc(void* v){
				Task* tmptsk = (Task*)v;
				char* str = (char*)tmptsk->description;
        if (strstr(str, filter) != NULL) return true;
        else return false;
    }
    
    LList* matches = llfilter(list->list, *filterfunc);
    Tasklist* t = tasklist_new();
    t->list = matches;
    return t;
}

// Print out a tasklist to the console.
int tasklist_display(Tasklist* list){

    int count = 0;
    void print_task(void* item){
        Task* t = (Task*)item;
        printf("%d: %s\n", count, t->description);
        count ++;
    }
    llapply(list->list, &print_task);
    return count;
}

// Write a tasklist to a file.
int tasklist_dump(Tasklist *list, FILE* f){
    void d(void* item){
        Task* t = (Task*)item;
        fprintf(f, "%s\n", task_dump(t));
    }
    llapply(list->list, &d);
    return 0;
}

// Read a tasklist from a file.
int tasklist_read(Tasklist *list, FILE* f){

    // Go through the file one line at a time.
    char buffer[256];
    while (fgets(buffer, 255, f) != NULL){
        
        // Remove the ending newline.
        char* start = buffer;
        int newline = strcspn(buffer, "\n");
        start[newline] = '\0';

        // Make a task to hold the line.
        Task* temp = task_new();
        task_append(temp, buffer);

        // Add it to the list.
        tasklist_append(list, temp);
    }
    return 0;
}
