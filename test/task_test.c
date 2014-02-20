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
    task_append(task, "x (A) 2013-09-25 Testing task.");
    char* dump = (char*)task_dump(task);
		debug("taskdump = '%s'", dump);
    sp_assert(strcmp("x (A) 2013-09-25 Testing task.", dump) == 0, 
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
    task_set_complete(task, true);
    debug("Task = '%s'", task_dump(task));
    sp_assert(strcmp(task_dump(task), "x Testing completion") == 0, 
            "Task completion did not work");
    task_free(task);
}

void parse_test(){
	//set up the vars
	int tsknum = 6;
	Task* task[tsknum];
	int i;
	for (i = 0; i < tsknum; i++)
		task[i] = task_new();
    
    //set of test tasks
    char* testTasks[] = {
        "x task with nothing",
	    "(A) task with prio only",
        "2013-03-02 task with date only",
        "(B) 2013-03-02 task with date and prio",
        "x (C) 2013-03-02 complete task"
    };

	//test valid task_parse calls
    for (i = 0; i < tsknum-1; i++) {
        task_parse(task[i], testTasks[i]);
    }
	//test invalid task_parse calls
	sp_assert(task_parse(task[5], "invalid task (D) form 2013-03-02"), "task_parse failed for invalid task format");
	sp_assert((task_parse(NULL,"a null task string") == 0), "task_parse does not fail with NULL task");
	sp_assert(task_parse(task[0],"") == 0, "task_parse does not fail with empty string");
	sp_assert(task_parse(task[0], NULL) == 0, "task_parse does not fail with NULL string");

	//check for valid returns	
	
	//uncomment to print out actual values for further debugging
/*
 * 	for (i = 0; i < tsknum; i++)
 * 	{
 * 		Task* tsk = task[i];
 * 		if(!tsk) 
 * 		{
 * 			printf("\nTask[%i] failed to parse\n",i);
 * 			continue;
 * 		}
 * 		printf("\nTask[%i]\n-----------\n",i);
 * 		printf("descript: %s\n", tsk->description);
 * 		printf("prio: %c\n", tsk->priority);
 * 		printf("complete: %i\n", tsk->complete);
 * 		printf("datestamp: %i\n", tsk->datestamp);
 * 	}
 * 
 *  */

	for (i = 0; i < tsknum; i++)
	{
		Task* tsk = task[i];
		char* output = task_dump(tsk);
		switch(i)
		{
			case 0: 
				sp_streql(output, testTasks[i], "task_parse fails with simple task");
				break;
			case 1: 
				sp_streql(output, testTasks[i], "task_parse fails with task containing priority only");
				break;
			case 2: 
				sp_streql(output, testTasks[i], "task_parse fails with task containing date only");
				break;
			case 3: 
				sp_streql(output, testTasks[i], "task_parse fails with task containing prio and date");
				break;
			case 4: 
				sp_streql(output, testTasks[i], "task_parse fails with complete task with prio and date");
				break;
            default:
                debug("Case not given...");
		}
	}

	for (i = 0; i < tsknum; i++)
		task_free(task[i]);

}

void task_compare_test(){
    Task* done = task_new();
    Task* not_done = task_new();
    task_set_complete(done, true);
    task_set_complete(not_done, false);
    int comp = task_default_compare(done, not_done);
    sp_assert(comp > 0, "Comparison of done vs not done inaccurate");
}

void task_fixture(){
    sp_run_test(append_test);
    sp_run_test(dump_test);
    sp_run_test(keyword_test);
    sp_run_test(complete_test);
    sp_run_test(task_compare_test);
//    sp_run_test(parse_test);
}
