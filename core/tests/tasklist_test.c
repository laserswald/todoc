#include "task.h"
#include "tasklist.h"
#include "util/speedunit.h"
#include <string.h>

Tasklist* make_three_item_list(){
    Tasklist *list = tasklist_new();
    Task *first, *second, *third;
    first = task_new();
    second = task_new();
    third = task_new();
    task_append(first, "This is the first task. #first");
    task_append(second, "This is the second task. #notfirst");
    task_append(third, "This is the third task. #notfirst");
    tasklist_append(list, first);
    tasklist_append(list, second);
    tasklist_append(list, third);
    return list;
}

Tasklist* make_single_item_list(){
    Tasklist *list = tasklist_new();
    Task *newtask = task_new();
    task_append(newtask, "Something important I need to do.");
    tasklist_append(list, newtask);
    return list;
}

sp_test(tlist_append_test){
    // Basic setup.
    Tasklist* list = make_single_item_list();
    /* Is the task in the correct spot? */
    Task* t = tasklist_get(list, 0); 
    sp_assert(t != NULL, "Tasklist did not append for some reason.");
    /* Is it the right task? */ 
    sp_streql(t->description, "Something important I need to do.", "Task's description is not equal."); 

    /* Add another task. */
    Task* secondary = task_new();
    task_append(secondary, "A second thing.");
    tasklist_append(list, secondary);
    Task* segundo = tasklist_get(list, 1);
    sp_assert(segundo != NULL, "Task is the only task.");
    sp_streql(segundo->description, "A second thing.", "Second task is not correct.");

    tasklist_free(list);

    return NULL;
}

sp_test(tlist_get_test){
    Tasklist* list = make_three_item_list();
    Task* secondItem = tasklist_get(list, 1);
    sp_streql(task_dump(secondItem), "This is the second task. #notfirst", "task gotten was not the right one.");
    tasklist_free(list);
    return NULL;
}

sp_test(tlist_search_test){
    Tasklist* list = make_three_item_list();
    Tasklist* notfirst = tasklist_search(list, "notfirst");
    sp_assert(notfirst != NULL, "Task list did not find anything.");
    List* nlist = notfirst->list;
    int i;
    for (i = 0; i < nlist->length; i++){
        Task* t = (Task*)List_get(nlist, i);
        // TODO: Check if this exists.
        sp_assert(t, "Task is nonexistent.");
        sp_assert(strstr(t->description, "notfirst") != NULL, "Task was found with no keyword");
    } 
    tasklist_free(list);
    return NULL;
}

sp_test(tlist_remove_test){
    Tasklist* list = make_three_item_list();
    Task* task = tasklist_remove(list, 1);
    sp_streql("This is the second task. #notfirst", task->description,
                "Second task was not correct.");
    sp_streql("This is the third task. #notfirst", task_dump(tasklist_get(list, 1)), "Third task was in wrong place.");

    task_free(task);
    task = tasklist_remove(list, 0);
    debug("Task info: '%s'", task->description);
    sp_streql("This is the first task. #first", task->description, "First task no longer exists.");
    return NULL;

}

sp_test(tlist_load_test){
    Tasklist *list = tasklist_new();
    FILE* f = fopen("core/tests/testtodo.txt", "r");
    sp_assert(f, "File does not exist");
    tasklist_read(list, f);
    Task* gotten = tasklist_get(list, 0);
    debug("Aquired task: '%s'", gotten->description);
    sp_streql(gotten->description, "A test task in a file.", "Task was not read correctly.");
    return NULL;
}

sp_test(tasklist_fixture){
    sp_run_test(tlist_append_test);
    sp_run_test(tlist_get_test);
    sp_run_test(tlist_remove_test);
    sp_run_test(tlist_search_test);
    sp_run_test(tlist_load_test);
    return NULL;
}
