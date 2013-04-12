#ifndef _LLIST
#define _LLIST

struct element{
    struct element* prev;
    struct element* next;
    void* data;
};

struct llist {
    struct element* head;
    struct element* tail;
    int length;
};
typedef struct llist LList;

#define INDEX_NONEXISTENT -30

LList* new_llist();

int destroy_llist(LList* list);

/** Adds an item to a list.
 * Adds an item to the back of the list, where the back is defined as the
 * tail end of the list.
 * @param: list the list to add to.
 * @param: thingy a void pointer to the item to add.
 * returns 0 if everything went correctly; if not 0 then something goofed.
 */
int lladd(LList* list, void* thingy);

// Removes an element from a list.
int llrem(LList* list, int index);

// Returns a pointer to a list value.
void* llget(LList* list, int index);

// Applies a function over a list.
int llapply(LList* list, void (*function)(void*));

// Runs the function over the list, returning a changed list.
LList* llmap(LList* list, void* (*function)(void*));

#endif//LLIST
