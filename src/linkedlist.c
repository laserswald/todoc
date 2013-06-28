/* linkedlist.c
 *
 * A basic linked list implementation.
 */ 
#include "stdio.h"
#include "stdlib.h"
#include "linkedlist.h"

LList* new_llist(){
    LList* this = (LList*)malloc(sizeof(LList));

    // Extra construction stuff....
    this->head = NULL;
    this->tail = NULL;
    return this;
}

LList* destroy_element(struct element* target){
    free(target);
}

int lladd(LList* l, void* item)
{
    struct element* elem = (struct element*) malloc(sizeof(struct element));
    if (elem == NULL){
        fprintf(stderr, "Could not create new linked list element.");
        goto error;
    }
    elem->data = item;
    elem->prev = NULL;
    elem->next = NULL;

    // No head of list, there is no list.
    if (l->head == NULL){
        l->head = elem;
        l->tail = elem;
        return 0;
    } else {
        l->tail->next = elem;
        elem->prev = l->tail;
        l->tail = elem;
    }
error:
    return -1;
}

struct element* slide(struct element* sl, int howmuch){
    int i;
    for (i = 0; i < howmuch; i++) {
        if (sl == NULL) {
            return NULL;
        }
        sl = sl->next;
    }
    return sl;
}

// Removes an item from the linked list.
void* llrem(LList* l, int index){
    struct element* slider = l->head;
    slider = slide(slider, index);
    if (slider == l->tail){l->tail = slider->prev;}
    else slider->next->prev = slider->prev;
    if (slider == l->head){l->head = slider->next;}
    else slider->prev->next = slider->next;
    void* data = slider->data;
    destroy_element(slider); 
    return data;
} 

void* llget(LList* l, int index){
    if (l == NULL || l->head == NULL || l->tail == NULL){
        return NULL;
    }
    void* item;
    struct element* slider = l->head;
    slider = slide(slider, index);
    if (slider == NULL){
        return NULL;
    }
    item = slider->data;
    return item;
}

int llapply(LList* list, void (*function)(void*)){
    struct element* current = list->head;
    while(current != NULL){
        (*function)(current->data);
        current = current->next;
    }
    return 0;
}

LList* llmap(LList* list, void* (*function)(void*)){
    LList* newlist = new_llist();
    struct element* current = list->head;
    while(current != NULL){
        lladd(newlist, (*function)(current->data));
        current = current->next;
    }
    return newlist;
}

LList* llfilter(LList* list, bool (*fun)(void*)){
    LList* newlist = new_llist();
    struct element* current = list->head;
    while(current != NULL){
        if ((*fun)(current->data)){
            lladd(newlist, current->data);
        }
        current = current->next;
    }
    return newlist;
}

// Destroys the linked list.
int destroy_llist(LList* list)
{
    if (!list) return;
    if (!(list->head)){free(list); return;}
    struct element* index = list->head;
    struct element* previous = NULL;
    while (index){
        previous = index;
        index = index->next;
        free(previous);
    }
    free(list);
}
