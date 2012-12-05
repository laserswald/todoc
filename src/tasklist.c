
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
    this->task = NULL;
    this->next = NULL;
    return this;
}

// Destroy the given tasklist.
void tasklist_free(Tasklist* list){
    if (list == NULL) return;
    task_free(list->task);
    tasklist_free(list->next); 
    free(list);
}

// Add a new task to the end of this list.
int tasklist_append(Tasklist* this, Task* t){
    if (this == NULL){
        // Make sure it's heard.
        return 1;
    }
    Tasklist* index = this;
    //Probably sure we can move this to another function.
    while (index->task != NULL && index->next != NULL){
        index = index->next;
    }
    // Stopped because this task is null.
    if (index->task == NULL){
        index->task = t;
   } else { //Stopped because of the end of the list.
        Tasklist* new = tasklist_new();
        new->task = t;
        index->next = new;
    }
    return 0;
}

// Get the task at the index.
Task* tasklist_get(Tasklist* list, int index){
    if (!list || !list->task && !list->next) {
        return NULL;
    }
    Tasklist* slider = list;
    int i = 0;
    while (i < index && slider->next != NULL){
        slider = slider->next;
        i++;
    }
    return slider->task;
}

// Remove the task at the index.
Tasklist* tasklist_remove(Tasklist* list, int index){
    if (!list || !list->task && !list->next) {
        return NULL;
    }
    Tasklist* slider = list;
    int i = 0;
    while (i < index-1){
        slider = slider->next;
    }
    Tasklist* removed = slider->next;
    slider->next = slider->next->next;
    return removed;
}

// Construct a tasklist of tasks that match the filter.
Tasklist* tasklist_search(Tasklist* list, char* filter){
    
    // Make sure the list exists; if not return NULL
    if (!list || !list->task && !list->next){
        puts("Empty tasklist.");
        return NULL;
    }
    
    // Make a list to hold the matches.
    Tasklist* matches = tasklist_new();
    Tasklist* current = list;
    while (current != NULL){ 
        if (task_has_keyword(current->task, filter)){
            tasklist_append(matches, current->task);
        }
        current = current->next;
    }
    return matches;
}

// Print out a tasklist to the console.
int tasklist_display(Tasklist* list){
    Tasklist* iter = list;
    int count = 0;
    while(iter != NULL && iter->task != NULL){
        printf("%d: %s", count, task_dump(iter->task));
        iter = iter->next;
        count++;
    }
    return count;
}

// Write a tasklist to a file.
int tasklist_dump(Tasklist *list, char* filename){
    // Open the file and check if anything broke.
    FILE* f = fopen(filename, "w");
    if (f == NULL){
        return 1;
    }
    // Make a reference to the list to iterate over.
    Tasklist *iter = list;

    // Go through the tasklist, writing to the file.
    while (iter != NULL){
        fprintf(f, "%s", task_dump(iter->task));
        iter = iter->next;
    }
    // Close the file.
    fclose(f);
    return 0;
}

// Read a tasklist from a file.
int tasklist_read(Tasklist *list, char* filename){

    // Open the file and check if it broke.
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        puts("Could not open file for tasklist writing.");
        return 1;
    }
    
    // Make a reference to the list to iterate over.
    Tasklist* iter = list;
    
    // Moves the index to the end.
    while (iter->next){
        iter = iter->next;
    }

    // Go through the file one line at a time.
    char buffer[256];
    while (fgets(buffer, 255, f) != NULL){
        
        // Remove the ending newline.
        char* start = buffer;
        char* endOfString = strchr(buffer, '\n');
        if (endOfString != NULL){
            endOfString = '\0';
        }

        // Make a task to hold the line.
        Task* temp = task_new();
        task_append(temp, buffer);

        // Add it to the list.
        tasklist_append(list, temp);
    }
    fclose(f);
    return 0;
}
