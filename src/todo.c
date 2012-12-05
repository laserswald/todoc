// Todo.c: the main file. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "task.h"
#include "tasklist.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_BUILD 1

int add_task(char* filename, char* string){

    puts("-- Adding new task.");

    Tasklist* list = tasklist_new();
    Task* task = task_new();
    
    if (tasklist_read(list, filename) != 0){
        puts("ERROR: could not read tasklist.");
        goto error;
    }
    
    task_append(task, string);   
    tasklist_append(list, task);
    if (tasklist_dump(list, filename) != 0){
        puts("ERROR: could not write tasklist.");
        goto error;
    }
    
    printf("-- Added:\n%s\n", string);
    tasklist_free(list);
    return 0;

    error:
        return 1;
}

// TODO: Make this say more stuff.
// Warning: untested.
int list_tasks(char* filename){
    puts("-- Listing all tasks.");
    Tasklist* list = tasklist_new();
    tasklist_read(list, filename);
    tasklist_display(list);
}

/** List the tasks with a match in the string.
 *
 */
void list_tasks_matching(char* filename, char* string){
    printf("-- Listing matches for '%s'\n", string);
	Tasklist* list = tasklist_new();
    tasklist_read(list, filename);
    Tasklist* matches = tasklist_search(list, string);
    int count = tasklist_display(matches);
    if (count == 0){
        puts("No matches.");
    } else {
        printf("Number of matches: %d.\n", count);
    }
}

// Removes a task given the filename and the index.
int remove_task(char* filename, int number){
    // Open up the tasklist.
    Tasklist* list = tasklist_new();
    if (tasklist_read(list, filename) != 0){
        puts("ERROR: could not read tasklist.");
        goto error;
    }
    Task* t = tasklist_get(list, number);
    printf("Are you sure you want to remove %d: %s? (y/n)", number, task_dump(t));
    char answer[5];
    char* ans = answer;
    fgets(ans, 5, stdin);
    if (strcmp(answer, "y\n") == 0){
        puts("-- Removing task.");
        tasklist_remove(list, number);
        if (tasklist_dump(list, filename) != 0){
            puts("ERROR: could not write tasklist.");
        }
    }
    error:
        return 1;
}

/** Complete a task.
 *
 */
void complete_task(char* filename, int number)
{
    printf("-- Completing task number %d.", number);
    Tasklist* list = tasklist_new();
    tasklist_read(list, filename);
    Task* task = tasklist_get(list, number);
    task_complete(task);
    tasklist_dump(list, filename);
    printf(" #%d complete.\n", number);
}

void print_help(){
    printf("todoc version %d.%d.%d by Ben Davenport-Ray and contributors.\n", VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);
}

bool strings_equal(char* subject, char* first, char* sec){
    if(strcmp(subject, first) == 0 ||
       strcmp(subject, sec) == 0){
        return true;
    } else {
        return false;
    }
}

int main(int argc, char* argv[]){

    char* taskfile = "todo.txt";
    char* donefile = "done.txt";

    bool verbose = false;

    int status = EXIT_SUCCESS;
    // parse the command line arguments.
    int i;
    for (i = 0; i < argc; i++){
        // Add a new task.
        if (strings_equal(argv[i], "add", "-a")){
            if (add_task(taskfile, argv[i+1]) != 0){
                status = EXIT_FAILURE;
            }
            i++;
            continue;
        }

        // Remove a task.
        if (strings_equal(argv[i], "remove", "-r")){
            int index = atoi(argv[i+1]);
            if (remove_task(taskfile, index) != 0){
                status = EXIT_FAILURE;
            }
            i++;
            continue;
        }

        // Complete a task.
        if (strings_equal(argv[i], "do", "-d")){
            int index = atoi(argv[i+1]);
            complete_task(taskfile, index);
            i++;
            continue;
        }
        
        // List the tasks matching the string in the file.
        if (strings_equal(argv[i], "search", "-s")){
            list_tasks_matching(taskfile, argv[i+1]);
            i++;
            continue;
        }
        
        // Show all the tasks in the file.
        if(strings_equal(argv[i], "list", "-l")){
            list_tasks(taskfile);
            continue;
        }
        
        // Show the help dialog.
        if (strcmp(argv[i], "-h") == 0){
            print_help();
        }

        // Set the taskfile flag.
        if (strcmp(argv[i], "-f") == 0){
            taskfile = argv[i+1];
            i++;
            continue;
        }

        // Set the verbosity flag.
        if (strcmp(argv[i], "-v") == 0){
            verbose = true;
        }
    }

    puts("-- Done.");
    return status;
}
