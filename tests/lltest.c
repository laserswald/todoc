#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "linkedlist.h"
#include "speedunit.h"
void add_test()
{
    LList* list = new_llist();
    sp_assert(list != NULL, "Created list is null.");

    int a = 56;
    void* va;
    int* ap = &a;
    va = ap;
    lladd(list, va);
    int* bp = (int*)list->head->data;
    int b = *bp;
    sp_assert(a == b, "Stored data is not equal to non-stored data");

    int c = 93;
    void *cv;
    int* cp = &c;
    cv = cp;
    lladd(list, cv);
    int* dp = (int*)list->head->next->data;
    int d = *dp;
    sp_assert(c == d, "Adding item to list already containing items failed.");

    destroy_llist(list);    
}

void rem_test(void){
    LList* list = new_llist();
    int items[] = {1, 2, 3};
    int i;
    for (i = 0; i < 3; i++) {
        int* ip = &items[i];
        void* vp = ip;
        lladd(list, vp);
    }
    
    llrem(list, 0);
    int* first = (int*)list->head->data;
    int f = *first;
    sp_assert(f == 2, "Removal did not happen.");    
    
    llrem(list, 1);
    sp_assert(list->tail == list->head, "Removal from back messed up.");
}

void get_test(void){
    
}

void linkedlist_fixture()
{
    add_test();
    rem_test();
    get_test();
}
