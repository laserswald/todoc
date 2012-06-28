// Todo.c: the main file. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textdb.h"
#include "filter.h"

void add_task(char* filename, char* string){
    FILE* file;
    if ((file = fopen(filename, "a")) == NULL){
        puts("File could not be opened.");
        abort();
    }
    fprintf(file, "%s\n", string);
    printf("Task added:\n%s\n", string);
}

int check_range_exp(int number, char* expression){
    char* end_num = strpbrk(expression, "-")+1;
    printf("second half of expression: %s", end_num);
    
}

// TODO: Make this say more stuff.
// Warning: untested.
int list_tasks(char* filename){
    FILE* file = fopen(filename, "r");
    if (!file){
        // Bugfix: make a new file when there is none.
        file = fopen(filename, "w+");
    }

    printf("Todo list in file '%s': \n", filename);
    int count = 0;
    char buffer[256];
    while((fgets(buffer, 255, file)) != NULL){
        printf("\t%d: %s", count, buffer);
        count++;
    } 
    printf("Total tasks: %d.\n", count);
}

/** List the tasks with a match in the string.
 *
 */
void list_tasks_matching(char* filename, char* string){
	FILE* file = fopen(filename, "r");
	char buffer[256];
    while(fgets(buffer, 255, file) != NULL){
        if (isIn(buffer, string)){
            printf("Match: %s", buffer);
        }
    }
}

/** Complete a task.
 *
 */
void complete_task(char* filename, int number)
{
    move_line(filename, "done.txt", number);
    printf("Task #%d complete.\n", number);
}

int main(int argc, char* argv[]){
    // TODO: optionally compile in custom argument parser.
    if (argc > 1){
        printf("Debug: Argv[1] = %s\n", argv[1]);
        if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "add") == 0){
            add_task("todo.txt", argv[2]);
        } 

        else if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "rem") == 0){
            puts("Debug: removing task");
            remove_line("todo.txt", "todo.txt~", atoi(argv[2]));
        }

        else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "do") == 0){
            puts("Debug: completing task");
            complete_task("todo.txt", atoi(argv[2]));
        }

        else if (strcmp(argv[1], "-l") == 0){
            if (argc = 3) 
	            list_tasks_matching("todo.txt", argv[2]);
            }
    } 
    else { 
        list_tasks("todo.txt");
    }
    return 0;
}
