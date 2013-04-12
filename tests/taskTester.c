#include "seatest.h"
#include "task.h"


void task_setup(){
}

void append_test(){
    struct task_t* task = NULL;
    task = task_new();
    
    // Tests adding to blank task.
    task_append(task, "Items.");
    assert_string_equal(task->description, "Items.");
    
    // Tests adding to NULL pointer.
    int error = task_append(NULL, "derp.");
    // Make sure that the error is returned.
    assert_true(error);
}

void dump_test(){
    struct task_t *task = task_new();
    task_append(task, "Testing task.");
    char* dump = (char*)task_dump(task);
    assert_string_equal("Testing task.", dump);
}

void keyword_test(){
    struct task_t *task = task_new();
    task_append(task, "Testing search.");
    int has = task_has_keyword(task, "search");
    assert_true(has);
}

void task_fixture(){
    test_fixture_start();
    
    
    fixture_setup(task_setup);

    run_test(append_test);
    run_test(dump_test);
    run_test(keyword_test);
    //run_test(read_test);

    test_fixture_end();
}

