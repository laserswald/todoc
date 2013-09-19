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
	//set up the vars
	int tsknum = 6;
	Task* task[tsknum];
	int i;
	for (i = 0; i < tsknum; i++)
		task[i] = task_new();

	//parse them
	task_parse(task[0], "task with nothing");
	task_parse(task[1], "(A) task with prio only");
	task_parse(task[2], "2013-03-02 task with date only");
	task_parse(task[3], "(B) 2013-03-02 task with date and prio");
	task_parse(task[4], "x (C) 2013-03-02 complete task");
	task_parse(task[5], "invalid task (C) form 2013-03-02");

	//check for valid returns	
	for (i = 0; i < tsknum; i++)
	{
		Task* tsk = task[i];
		if(!tsk) 
		{
			printf("\nTask[%i] failed to parse\n",i);
			continue;
		}
		printf("\nTask[%i]\n-----------\n",i);
		printf("descript: %s\n", tsk->description);
		printf("prio: %c\n", tsk->priority);
		printf("complete: %i\n", tsk->complete);
		printf("datestamp: %i\n", tsk->datestamp);
	}
}

void task_fixture(){
//    sp_run_test(append_test);
//    sp_run_test(dump_test);
//    sp_run_test(keyword_test);
//    sp_run_test(complete_test);
    sp_run_test(parse_test);
}
