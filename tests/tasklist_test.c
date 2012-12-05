#include "task.h"
#include "tasklist.h"
#include "seatest.h"

#include <string.h>

struct tasklist_t* make_three_item_list(){
    struct tasklist_t *list = tasklist_new();
    struct task_t *first, *second, *third;
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

struct tasklist_t* make_single_item_list(){
    struct tasklist_t *list = tasklist_new();
    struct task_t *newtask = task_new();
    task_append(newtask, "Something important I need to do.");
    tasklist_append(list, newtask);
    return list;
}

void tlist_append_test(){
    // Basic setup.
    struct tasklist_t* list = make_single_item_list();
    /* Is the task in the correct spot? */
    assert_true(list->task != NULL);
    /* Is it the right task? */
    assert_string_equal(list->task->description, "Something important I need to do."); 

    /* Add another task. */
    struct task_t* secondary = task_new();
    task_append(secondary, "A second thing.");
    tasklist_append(list, secondary);
    assert_true(list->next != NULL && list->next->task != NULL);
    assert_string_equal(list->next->task->description, "A second thing.");
    tasklist_free(list);
}

void tlist_get_test(){
    struct tasklist_t* list = make_three_item_list();
    struct task_t* secondItem = tasklist_get(list, 1);
    assert_string_equal(task_dump(secondItem), "This is the second task. #notfirst");
    tasklist_free(list);
}

void tlist_search_test(){
    struct tasklist_t* list = make_three_item_list();
    struct tasklist_t* notfirst = tasklist_search(list, "notfirst");
    assert_true(notfirst != NULL);
    struct tasklist_t *index = notfirst;
    while (index != NULL){
        assert_true(strstr(index->task->description, "notfirst") != NULL);
        //assert_fail(strstr(index->task->description, "notfirst") == NULL);
        index = index->next;
    }
    tasklist_free(list);
}

void tlist_remove_test(){
    struct tasklist_t* list = make_three_item_list();
    struct tasklist_t* taskl = tasklist_remove(list, 1);
    assert_string_equal(taskl->task->description, "This is the second task. #notfirst");
    assert_string_equal(task_dump(tasklist_get(list, 1)),  "This is the third task. #notfirst");
    assert_string_equal("This is the first task. #first", task_dump(tasklist_remove(list, 0)));

}

void tlist_load_test(){
    struct tasklist_t *list = tasklist_new();
    tasklist_read(list, "tests/testtodo.txt");    
    assert_string_equal(list->task->description, "A test task in a file.\n");
}

void tasklist_fixture(){
    test_fixture_start();
    run_test(tlist_append_test);
    run_test(tlist_get_test);
    run_test(tlist_remove_test);
    run_test(tlist_search_test);
    run_test(tlist_load_test);
    test_fixture_end();   
}
