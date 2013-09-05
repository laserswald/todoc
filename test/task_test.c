
#include <stdbool.h>
#include "task.h"
#include "speedunit.h"
#include "dbg.h"
void task_setup(){
}

void append_test(){
    Task* task = NULL;
    task = task_new();
    
    // Tests adding to blank task.
    task_append(task, "Items.");
    sp_assert(strcmp(task->description, "Items.") == 0, 
                        "Task description and input items are unequal.");
    
    // Tests adding to NULL pointer.
    int error = task_append(NULL, "derp.");
    // Make sure that the error is returned.
    sp_assert(error != 0, "Error code was not returned.");
    task_free(task);
}

void dump_test(){
    Task *task = task_new();
    task_append(task, "Testing task.");
    char* dump = (char*)task_dump(task);
    sp_assert(strcmp("Testing task.", dump) == 0, 
                        "Dumped task is not the same as given task information.");
    task_free(task);
}

void keyword_test(){
    Task *task = task_new();
    task_append(task, "Testing search.");
    int has = task_has_keyword(task, "search");
    sp_assert(has != false, "Search did not find the word.");
    task_free(task);
}

void complete_test(){
    Task * task = task_new();
    task_append(task, "Testing completion");
    task_complete(task);
    debug("Task = '%s'", task_dump(task));
    sp_assert(strcmp(task_dump(task), "x Testing completion") == 0, 
            "Task completion did not work");
    task_free(task);
}

void parse_test(){
    Task* task = task_new();
    task_parse(task, "A pretty simple task");
    // It should look the same as the parsed string.
    char* string = (char*)task_dump(task);
    sp_assert(strcmp(string, "A pretty simple task") == 0, "Standard parsing did not work");
    // Tests the completion status.
    sp_assert(task->complete == false, "Task's completion status was not updated correctly");
    // Test that the description is the same as the given string.
    sp_assert(strcmp(task->description, "A pretty simple task") == 0, "Description is not the same");


    Task* completetask = task_new();
    task_parse(completetask, "x A complete task");
    
}

void task_fixture(){
    sp_run_test(append_test);
    sp_run_test(dump_test);
    sp_run_test(keyword_test);
    sp_run_test(complete_test);
    // parse_test(); 
}
