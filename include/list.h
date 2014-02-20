// My own Linked List implementation.
//

#ifndef __LLIST__
#define __LLIST__
#include "dbg.h"
#include <stdbool.h>

typedef struct listelem{
    struct listelem* prev;
    struct listelem* next;
    void* data;
}ListNode;

struct llist {
    ListNode* head;
    ListNode* tail;
    int length;
};
typedef struct llist List;

List* List_new();

int List_free(List* this);

/** Adds an item to a list.
 * Adds an item to the back of the list, where the back is defined as the
 * tail end of the list.
 * @param: list the list to add to.
 * @param: thingy a void pointer to the item to add.
 * returns 0 if everything went correctly; if not 0 then something goofed.
 */
int List_append(List* list, void* thingy);

// Adds an item from the back of the list.
void* List_retrieve(List* list);

// Removes the first element from the list.
void* List_pop(List* list);

// Adds to the front of the list.
int List_push(List* list, void* item);

// Returns a pointer to a list value.
void* List_get(List* list, int index);

// Removes an arbitrary element from a list.
void* List_remove(List* list, int index);

List* List_sort(List* list, int (*cmp)(void*, void*));

// Want functional style? Why not?

// Applies a function over a list.
int List_do(List* list, void (*function)(void*));

// Runs the function over the list, returning a changed list.
List* List_map(List* list, void* (*function)(void*));

// Returns a new list that matches the function.
List* List_filter(List* list, bool (*function)(void*));
#endif//LLIST
