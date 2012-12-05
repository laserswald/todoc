#include "seatest.h"
#include "task.h"

#include <assert.h>

void task_setup(){
}

void append_test(){
    Task* task = NULL;
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
    Task *task = task_new();
    task_append(task, "Testing task.");
    char* dump = (char*)task_dump(task);
    assert_string_equal("Testing task.", dump);
}

void keyword_test(){
    Task *task = task_new();
    task_append(task, "Testing search.");
    int has = task_has_keyword(task, "search");
    assert_true(has);
}

void complete_test(){
    Task * task = task_new();
    task_append(task, "Testing completion");
    task_complete(task);
    assert_true(strcmp(task_dump(task), "x Testing completion") == 0);
}

void parse_test(){
    Task* task = task_new();
    task_parse(task, "A pretty simple task");
    // It should look the same as the parsed string.
    assert_string_equal(task_dump(task), "A pretty simple task");
    // Tests the completion status.
    assert_true(task->complete == false);
    // Test that the description is the same as the given string.
    assert_string_equal(task->description, "A pretty simple task");


    Task* completetask = task_new();
    task_parse(completetask, "x A complete task");
}

void task_fixture(){
    test_fixture_start();
    
    
    fixture_setup(task_setup);

    run_test(append_test);
    run_test(dump_test);
    run_test(keyword_test);
    run_test(complete_test);
    //run_test(read_test);

    test_fixture_end();
}

