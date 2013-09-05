
/* list.c
 *
 * A basic doubly linked list implementation.
 */ 
#include "stdio.h"
#include "stdlib.h"
#include "list.h"

List* List_new(){
    List* this = (List*)malloc(sizeof(List));
    // Extra construction stuff....
    this->head = NULL;
    this->tail = NULL;
    return this;
}

int destroy_element(ListNode* target){
    free(target);
    return 0;
}

int List_add(List* l, void* item){
    check(l, "List does not exist");

    ListNode* elem = (ListNode*) malloc(sizeof(ListNode));
    check_mem(elem);
    elem->data = item;
    elem->prev = NULL;
    elem->next = NULL;

    // No head of list, there is no list.
    if (l->head == NULL){
        l->head = elem;
        l->tail = elem;
    } else {
        l->tail->next = elem;
        elem->prev = l->tail;
        l->tail = elem;
    }

    l->length = l->length + 1;
    return 0;

    error:
    if (elem) destroy_element(elem);
    return -1;
}

ListNode* slide(ListNode* sl, int howmuch){
    // checks for stupid
    check(sl, "List node does not exist.");
    if (howmuch == 0) return sl;

    // remove the sign and put it into direction.
    int direction = 0;
    if (howmuch >= 0) direction = 1;
    else direction = -1;
    howmuch = abs(howmuch);
    
    // Move over that much.
    int i;
    for (i = 0; i < howmuch; i++) {
        check(sl, "End of list reached.");
        if (direction < 0){
            sl = sl->prev;
        } else {
            sl = sl->next;
        }
    }
    return sl;

    // On error.
    error:
    return NULL;
}

// Removes an item from the linked list.
void* List_remove(List* l, int index){
    check(l, "Given list is null.");
    ListNode* slider = l->head;
    check(slider, "list head is nothing.");
    slider = slide(slider, index);
    check(slider, "Index is out of list boundaries.");
    
    if (slider == l->tail){l->tail = slider->prev;}
    else slider->next->prev = slider->prev;
    if (slider == l->head){l->head = slider->next;}
    else slider->prev->next = slider->next;
    void* data = slider->data;
    
    destroy_element(slider); 
    return data;

    error:
    if (slider) free(slider);
    return NULL;
} 

void* List_get(List* l, int index){
    check(l, "No list.");

    void* item;
    ListNode* slider = l->head;
    check(slider, "List is empty.");

    slider = slide(slider, index);
    if (slider == NULL){
        log_err("No list element with that index.");
        return NULL;
    }
    item = slider->data;
    return item;

error:
    return NULL;    
}

int List_do(List* list, void (*function)(void*)){
    ListNode* current = list->head;
    while(current != NULL){
        (*function)(current->data);
        current = current->next;
    }
    return 0;
}

List* List_map(List* list, void* (*function)(void*)){
    List* newlist = List_new();
    ListNode* current = list->head;
    while(current != NULL){
        List_add(newlist, (*function)(current->data));
        current = current->next;
    }
    return newlist;
}

List* List_filter(List* list, bool (*fun)(void*)){
    List* newlist = List_new();
    ListNode* current = list->head;
    while(current != NULL){
        if ((*fun)(current->data)){
            List_add(newlist, current->data);
        }
        current = current->next;
    }
    return newlist;
}

// Destroys the linked list.
int List_free(List* list)
{
    if (!list) return -1;
    
    ListNode* index = list->head;
    ListNode* previous = NULL;
    while (index){
        previous = index;
        index = index->next;
        free(previous);
    }
    return 0;
}
