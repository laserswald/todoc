
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"
#include "speedunit.h"
#include "dbg.h"

static List* list = NULL;
char* first = "one";
char* second = "two";
char* third = "three";
char* testarray[] = {"two", "one", "three"};

void assertlistvals(List* l, char* vals[]){
    ListNode* ln = l->head;
    int i = 0;
    for ( ; ln; i++, ln=ln->next){
        sp_streql(vals[i], (char*)ln->data, "Lists are unequal.");
    }  
}

void list_alloc_test(){
    list = List_new();
    sp_assert(list != NULL, "List is null.");
    sp_assert(list->head == NULL, "List does not nullify head pointer");
    sp_assert(list->tail == NULL, "List does not nullify tail pointer");
    sp_assert(list->length == 0, "List length is not zero"); 
}

void add_get_test(){
    List_append(list, first);
    char* f = List_get(list, 0);
    sp_assert(f == first, "Stored data is not equal to non-stored data");
}

void push_pop_test(){
    // Test: pop normal use
    char* popped = List_pop(list);
    sp_streql(popped, first, "Normal pop use not equal");
    // Test: pop on blank list
    popped = List_pop(list); 
    sp_assert(popped == NULL, "Pop returned something. That's strange.");
    // Test: push on blank list
    List_push(list, first);
    sp_assert(list->head->data == first, "Pushing did not happen!");
    // Test: push on no list or
}

void remove_test(void){
    List_append(list, second);
    List_remove(list, 0);
    char *thingy = List_get(list, 0);
    sp_assert(thingy == second, "Removal did not happen.");    
    debug("thingy = %s", thingy);     
}

void applytestfn(void* v){
    char* item = v; 
    printf("Item: %s\n", item);
}

void do_test(void){
    List_append(list, first);
    List_append(list, third);
    List_do(list, &applytestfn); 
}

int stringcmp(void* a, void* b){
    char* as = a;
    char* bs = b;
    return strcmp(as, bs);
}

void list_sort_test(void){
    List* sorted = List_sort(list, &stringcmp);
    char* sortedarray[] = {"one", "three", "two"};
    assertlistvals(sorted, sortedarray); 
    List_free(sorted);
}

void list_free_test(){
    List_free(list);
}

void linkedlist_fixture()
{
    sp_run_test(list_alloc_test);
    sp_run_test(add_get_test);
    sp_run_test(push_pop_test);
    sp_run_test(remove_test);
    sp_run_test(do_test);
    sp_run_test(list_sort_test);
    sp_run_test(list_free_test);
}
