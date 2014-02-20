
/* list.c
 *
 * A basic doubly linked list implementation.
 */ 
#include "stdio.h"
#include "stdlib.h"
#include "list.h"

ListNode* listnode_new(void* item){
    ListNode* n = malloc(sizeof(ListNode));
    n->prev = NULL;
    n->next = NULL;
    n->data = item;
    return n;
}

List* List_new(){
    List* this = (List*)malloc(sizeof(List));
    // Extra construction stuff....
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
    return this;
}


int destroy_element(ListNode* target){
    free(target);
    return 0;
}

int List_append(List* l, void* item){
    check(l, "List does not exist");

    ListNode* elem = listnode_new(item);
    check_mem(elem);

    // No head of list, there is no list.
    if (l->head == NULL && l->tail == NULL){
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

int List_push(List* l, void* item){
    check(l, "List does not exist");

    ListNode* elem = listnode_new(item);
    check_mem(elem);

    // No head of list, there is no list.
    if (l->head == NULL){
        l->head = elem;
        l->tail = elem;
    } else {
        l->head->prev = elem;
        elem->next = l->head;
        l->head = elem;
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
    l->length = l->length-1;
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
        log_err("No list element with index %d.", index);
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
        List_append(newlist, (*function)(current->data));
        current = current->next;
    }
    return newlist;
}

List* List_filter(List* list, bool (*fun)(void*)){
    List* newlist = List_new();
    ListNode* current = list->head;
    while(current != NULL){
        if ((*fun)(current->data)){
            List_append(newlist, current->data);
        }
        current = current->next;
    }
    return newlist;
}

void* List_pop(List* list){
    //return List_remove(list, 0);
    //TODO: Make sure the list is fine
    check(list, "No list.");
    // TODO: make sure the head is okay
    ListNode* head = list->head;
    if (head == NULL) goto error;
    list->head = list->head->next;
    if (list->head)
        list->head->prev = NULL;
    void* data = head->data;
    list->length = list->length - 1;
    return data;
error:
    return NULL;
}

/*
int List_push(List* list, void* data){
    ListNode* newdata = 
*/   

List* merge(List* l, List* r, int (*cmp)(void*, void*)){
    List* ret = List_new();
    void *lval, *rval;
    while (l->length != 0 || r->length != 0){ 
        lval = List_pop(l);
        rval = List_pop(r);
        if (lval == NULL && rval == NULL) {
            debug("Lists do not have accurate lengths; continuing.");
            break;
        } else if (lval == NULL){
            List_append(ret, rval);
        } else if (rval == NULL){
            List_append(ret, lval);
        } else {
            int bigger = cmp(lval, rval);
            if (bigger <= 0){
                List_append(ret, lval);
            }
            else List_append(ret, rval);
        }
    }
    return ret;
}

// Mergesort! 
List* List_sort(List* list, int (*cmp)(void*, void*)){
    // Choose the center value.
    if (list == NULL) return NULL;
    if (list->length == 0) return NULL; 
    if (list->length == 1) return list;
    int middle = list->length / 2;
    List *left = List_new();
    List *right = List_new();
    ListNode* ln = list->head;
    int i = 0;
    while(ln != NULL){
        if(i < middle) List_append(left, ln->data); 
        else if (i >= middle) List_append(right, ln->data);
        i++;
        ln = ln->next;
    }
    List_sort(left, cmp);
    List_sort(right, cmp);
    return merge(left, right, cmp);
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

