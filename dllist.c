/* dllist.c
 *
 * A doubly linked list implementation with clarity as priority (as well as some nice 
 * features). Rule #1. If you can't read it, it's useless to you. 
 */ 
#include "stdio.h"
#include "stdlib.h"
#include "dllist.h"

// Operations on list nodes.

// Allocate a new list node.
struct dlnode* dlnode_new(void* item){
    struct dlnode* n = malloc(sizeof(struct dlnode));
    n->prev = NULL;
    n->next = NULL;
    n->data = item;
    return n;
}

// Free a list node
void dlnode_free(struct dlnode* target){
    free(target);
}

// Link two nodes in this order.
void dlnode_link(struct dlnode *first, struct dlnode *second){
    if (first) { first->next = second; }
    if (second) { second->prev = first; }
}

// Remove links from this node. Also remove references to this node from the nodes that 
// this node links to.
void dlnode_unlink(struct dlnode *node){
    if (node->prev){
        node->prev->next = NULL;
    }
    if (node->next){
        node->next->prev = NULL;
    }
    node->prev = NULL;
    node->next = NULL;
}

struct dlnode* dlnode_seek(struct dlnode *haystack, int index){
    int i = 0; 
    struct dlnode* needle = haystack; 
    while (needle != NULL){
        if (i = index) return needle;
        i++;
        needle = needle->next;
    }
    return NULL;
}

// Operations on Doubly Linked lists

// Allocate a new doubly linked list.
dllist* dllist_new(){
    dllist* this = (dllist*)malloc(sizeof(dllist));
    // Extra construction stuff....
    dllist_init(this);
    return this;
}
// Initialize an already allocated list.
void dllist_init(dllist* this){
    this->head = NULL;
    this->tail = NULL;
}

// Append an item to the end of the list.
int dllist_append(dllist* l, void* item){
    if (!l) { 
        puts("dllist does not exist");
        return 1;
    }

    struct dlnode* elem = dlnode_new(item);
    if (!elem) {
        puts("element could not be created: no more memory");
    }

    // No head of list, there is no list.
    if (l->head == NULL && l->tail == NULL){
        l->head = elem;
        l->tail = elem;
    } else {
        dlnode_link(l->tail, elem);
        l->tail = elem;
    }

    return 0;

    error:
    if (elem) dlnode_free(elem);
    return 1;
}

// Push an item to the front of the list.
int dllist_push(dllist* l, void* item){
    if (!l) { 
        puts("dllist does not exist");
        return 1;
    }

    struct dlnode* elem = dlnode_new(item);
    if (!elem) {
        puts("element could not be created: no more memory");
    }

    // No head of list, there is no list.
    if (l->head == NULL){
        l->head = elem;
        l->tail = elem;
    } else {
        dlnode_link(elem, l->head);
        l->head = elem;
    }

    return 0;

    error:
    if (elem) dlnode_free(elem);
    return -1;
}

// Pop an item from the front of the list.
void* dllist_pop(dllist* l){
    if (!l) { 
        puts("list does not exist");
        return NULL;
    }
    struct dlnode* target = l->head;
    if (target == NULL)
        return NULL;

    void* data = target->data;
    
    l->head = target->next;
    dlnode_unlink(target);
    dlnode_free(target);
    return data;
}

// Retrieve an item from the back of the list.
void* dllist_retrieve(dllist* l){
    if (!l) { 
        puts("list does not exist");
        return NULL;
    }
    struct dlnode* target = l->tail;
    if (target == NULL) 
        return NULL;

    void* data = target->data;
    l->tail = target->prev;
    dlnode_unlink(target);
    dlnode_free(target);
    return data;
}

// How many links are in this list?
int dllist_count(dllist* l){
    if (!l) { 
        puts("list does not exist");
        return 0;
    }
    struct dlnode* current = l->head;
    int count;
    for (count = 0; current != NULL; count++, current=current->next);
    return count;
}

// Functional programming tools. 

// Execute the function over the list.
int dllist_do(dllist* list, void (*function)(void*)){
    struct dlnode* current = list->head;
    while(current != NULL){
        (*function)(current->data);
        current = current->next;
    }
    return 0;
}

// Return a list of each value returned from the function when each value of the list
// is passed to it.
dllist* dllist_map(dllist* list, void* (*function)(void*)){
    dllist* newlist = dllist_new();
    struct dlnode* current = list->head;
    while(current != NULL){
        dllist_append(newlist, (*function)(current->data));
        current = current->next;
    }
    return newlist;
}

// Return a list of the items that satisfy the predicate.
dllist* dllist_filter(dllist* list, bool (*fun)(void*)){
    dllist* newlist = dllist_new();
    struct dlnode* current = list->head;
    while(current != NULL){
        if ((*fun)(current->data)){
            dllist_append(newlist, current->data);
        }
        current = current->next;
    }
    return newlist;
}

// Merge two lists into one. (This is not a public function.)
static dllist* merge(dllist* l, dllist* r, int (*cmp)(void*, void*)){
    dllist* ret = dllist_new();
    void *lval = dllist_pop(l);
    void *rval = dllist_pop(r);
    while (dllist_count(l) != 0 || dllist_count(r) != 0){ 
        if (lval == NULL && rval == NULL) {
        } else if (lval == NULL){
            dllist_append(ret, rval);
        } else if (rval == NULL){
            dllist_append(ret, lval);
        } else {
            // 
            int comparison = cmp(lval, rval);
            if (comparison < 0){
                dllist_append(ret, lval);
                dllist_push(r, rval);
            } else {
                dllist_append(ret, rval);
                dllist_push(l, lval);
            }
        }
    }
    return ret;
}

// Mergesort the list.
dllist* dllist_sort(dllist* list, int (*cmp)(void*, void*)){
    if (list == NULL) return NULL;
    int count = dllist_count(list);
    if (count == 0) return NULL; 
    if (count == 1) return list;

    // Choose the center value.
    int middle = count / 2;
    dllist *left = dllist_new();
    dllist *right = dllist_new();
    struct dlnode* ln = list->head;
    int i = 0;
    while(ln != NULL){
        if(i < middle) dllist_append(left, ln->data); 
        else if (i >= middle) dllist_append(right, ln->data);
        i++;
        ln = ln->next;
    }
    left = dllist_sort(left, cmp);
    right = dllist_sort(right, cmp);
    return merge(left, right, cmp);
}


// Free the linked list from memory.
int dllist_free(dllist* list)
{
    if (!list) return -1;
    
    struct dlnode* index = list->head;
    struct dlnode* previous = NULL;
    while (index){
        previous = index;
        index = index->next;
        free(previous);
    }
    return 0;
}

