// Todo.c: the main file. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textdb.h"
#include "task.h"
#include "tasklist.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_BUILD 100

void add_task(char* filename, char* string){
    struct tasklist_t* list = tasklist_new();
    tasklist_read(list, filename);
    struct task_t* task = task_new();
    task_append(task, string);   
    tasklist_append(list, task);
    tasklist_dump(list, filename);
    printf(" added:\n%s\n", string);
    tasklist_free(list);
}

// TODO: Make this say more stuff.
// Warning: untested.
int list_tasks(char* filename){
    puts("Listing tasks....");
    struct tasklist_t* list = tasklist_new();
    tasklist_read(list, filename);
    tasklist_display(list);   
}

/** List the tasks with a match in the string.
 *
 */
void list_tasks_matching(char* filename, char* string){
	struct tasklist_t* list = tasklist_new();
    tasklist_read(list, filename);
    struct tasklist_t* matches = tasklist_search(list, string);
    int count = tasklist_display(matches);
    printf("Number of tasks: %d.\n");
}

void remove_task(char* filename, int number){
    
}

/** Complete a task.
 *
 */
void complete_task(char* filename, int number)
{
    //move_line(filename, "done.txt", number);
    printf(" #%d complete.\n", number);
}

void print_help(){
    printf("todoc version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);
}

int main(int argc, char* argv[]){

    char* taskfile = "todo.txt";
    char* donefile = "done.txt";

    // TODO: optionally compile in custom argument parser.
    if (argc > 1){
        printf("Debug: Argv[1] = %s\n", argv[1]);
        if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "add") == 0){
            add_task(taskfile, argv[2]);
        } 

        else if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "rem") == 0){
            puts("Debug: removing task");
           // remove_line("todo.txt", "todo.txt~", atoi(argv[2]));
        } else if (strcmp(argv[1], "-l") == 0){
		if (argc = 3) 
	        //list_tasks_matching("todo.txt", argv[2]);
            list_tasks("todo.txt");
       }

        else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "do") == 0){
            puts("Debug: completing task");
            //complete_task("todo.txt", atoi(argv[2]));
        }

        else if (strcmp(argv[1], "-l") == 0){
            if (argc = 3) 
	            list_tasks_matching(taskfile, argv[2]);
            }
    } 
    else { 
        list_tasks(taskfile);
    }
    puts("Done.");
    return 0;
}
