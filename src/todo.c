// Todo.c: the main file. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include "task.h"
#include "tasklist.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_BUILD 4

int add_task(char* filename, char* string){
    puts("-- Adding new task.");

    Tasklist* list = tasklist_new();
    Task* task = task_new();
    
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        perror("Could not open file.");
        goto error;
    }

    if (tasklist_read(list, file) != 0){
        puts("ERROR: could not read tasklist.");
        goto error;
    }
    
    task_append(task, string);   
    tasklist_append(list, task);
    if (tasklist_dump(list, file) != 0){
        puts("ERROR: could not write tasklist.");
        goto error;
    }
    
    printf("-- Added:\n%s\n", string);
    tasklist_free(list);
    return 0;

    error:
        return 1;
}

/** List the tasks in the file given.
 *
 */
int list_tasks(char* filename){
    // Open up the file, bro.

    FILE* file = fopen(filename, "r");
    if (file == NULL){
        perror("Could not open file");
        errno = 0;
        return -1;
    }
    puts("-- Listing all tasks.");
    Tasklist* list = tasklist_new();
    tasklist_read(list, file);
    tasklist_display(list);
    return 0;
}

/** List the tasks with a match in the string.
 *
 */
void list_tasks_matching(char* filename, char* string){
    
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        perror("Could not open file");
        errno = 0;
        return;
    }
    printf("-- Listing matches for '%s'\n", string);
	Tasklist* list = tasklist_new();
    tasklist_read(list, file);
    Tasklist* matches = tasklist_search(list, string);
    int count = tasklist_display(matches);
    if (count == 0){
        puts("No matches.");
    } else {
        printf("Number of matches: %d.\n", count);
    }
}

// Removes a task given the file and the index.
int remove_task(char* filename, int number){
    
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        perror("Could not open file");
        errno = 0;
        return;
    }
    // Open up the tasklist.
    Tasklist* list = tasklist_new();
    if (tasklist_read(list, file) != 0){
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
        if (tasklist_dump(list, file) != 0){
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
    FILE* file = fopen(filename, "r");
    tasklist_read(list, file);
    fclose(file);
    Task* task = tasklist_get(list, number);
    task_complete(task);
    file = fopen(filename, "w");
    tasklist_dump(list, file);
    fclose(file);
    printf(" #%d complete.\n", number);
}


// Help functions.
void print_version(){
    printf("todoc version %d.%d.%d by Ben Davenport-Ray and contributors.\n", VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);
}

void print_short_help(){ 
    puts("todoc [options] <command> [number] [description]");
}

void print_help(){
    print_short_help();
    puts("Manage tasks in a todo.txt file.\n");
    puts("Options:\n"
         " -f file \t\tSet the file used.\n"
         " -h \t\t\tShow the extended help.\n\n"
         "Commands:\n"
         " -a|add 'task'\t\tadds the task to the list\n"
         " -d|do index\t\tmarks the task at the index as done\n"
         " -r|remove index\tremoves the task at the index\n"
         " -s|search 'query'\tsearches for the text in the tasklist\n"
         " -l|list\t\tshows all the tasks\n");
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
    if (argc < 2){
        print_short_help();
        exit(status);
    }
    int i;
    for (i = 0; i < argc; i++){
        // Add a new task.
        if (strings_equal(argv[i], "add", "-a")){
            if (add_task(taskfile, argv[i+1]) != 0){
                status = EXIT_FAILURE;   // We done goofed.
            }
            i++;  // Skip the next argument.
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
            char* taskfilename = argv[i+1];
            
            i++;
            continue;
        }

        // Set the verbosity flag.
        if (strcmp(argv[i], "-v") == 0){
            verbose = true;
        }
    }

    //debugprint("Closing the file.");
    puts("-- Done.");
    return status;
}
