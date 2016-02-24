// Minimal C11 linked list
//

#ifndef __MINLLIST__
#define __MINLLIST__
#include <stdbool.h>

struct dlnode{
    void* data;
    struct dlnode* prev;
    struct dlnode* next;
};

// Operations on list nodes. Use with caution. Not as safe as below.
struct dlnode *dlnode_new(void*);
void dlnode_free(struct dlnode*);
void dlnode_link(struct dlnode*, struct dlnode*);
void dlnode_unlink(struct dlnode*);
struct dlnode *dlnode_seek(struct dlnode*, int);

typedef struct dllist {
    struct dlnode* head;
    struct dlnode* tail;
}dllist;

struct dllist* dllist_new(void);

void dllist_init(dllist*);

int dllist_free(dllist*);

// Adds to the back of a list.
int dllist_append(dllist*, void*);

// Gets an item from the back of the list.
void* dllist_retrieve(dllist*);

// Adds to the front of the list.
int dllist_push(dllist*, void*);

// Removes the first element from the list.
void* dllist_pop(dllist*);

dllist* dllist_map(dllist* list, void* (*function)(void*));

dllist* dllist_filter(dllist* list, bool (*fun)(void*));

int dllist_do(dllist*, void (*)(void*));

// Merge sorts the list with the given comparison function.
struct dllist* dllist_sort(dllist*, int (*)(void*, void*));

#endif//LLIST
