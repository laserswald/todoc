
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

void list_alloc_test(){
    list = List_new();
    sp_assert(list != NULL, "List is null.");
}

void add_get_test(){

    List_add(list, first);
    char* f = List_get(list, 0);
    sp_assert(f == first, "Stored data is not equal to non-stored data");

}

void remove_test(void){
    List_add(list, second);
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
    List_add(list, first);
    List_add(list, third);
    List_do(list, &applytestfn); 
}

void list_free_test(){
    List_free(list);
}

void linkedlist_fixture()
{
    sp_run_test(list_alloc_test);
    sp_run_test(add_get_test);
    sp_run_test(remove_test);
    sp_run_test(list_free_test);
}
