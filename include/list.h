// My own Linked List implementation.
//

#ifndef __LLIST__
#define _LLIST
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
int List_add(List* list, void* thingy);

// Removes an element from a list.
void* List_remove(List* list, int index);

void* List_pop(List* list);

List* List_filter(List* list, bool (*function)(void*));

// Returns a pointer to a list value.
void* List_get(List* list, int index);

// Applies a function over a list.
int List_do(List* list, void (*function)(void*));

// Runs the function over the list, returning a changed list.
List* List_map(List* list, void* (*function)(void*));

#endif//LLIST
