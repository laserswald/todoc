
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "textdb.h"

void add_task(char* filename, char* string){
    FILE* file;
    if ((file = fopen(filename, "a")) == NULL){
        puts("File could not be opened.");
        abort();
    }
    fprintf(file, "\n%s\n", string);
    printf("Task added:\n%s\n", string);
}

int check_range_exp(int number, char* expression){
    char* end_num = strpbrk(expression, "-")+1;
    printf("second half of expression: %s", end_num);
    
}

// TODO: This does nothing.
int check_in_exp(int number, char* expression){
    return 0;
}

// TODO: Make this say more stuff.
void list_tasks(char* filename){
    FILE* file = fopen(filename, "r");
    if (!file){
        puts("Could not open file.");
        return;
    }
    char buffer[256];
    while((fgets(buffer, 255, file)) != NULL){
        printf("%s", buffer);
    } 

}

// WARNING: Broken code!
void list_tasks_matching(char* filename, char* string){
	FILE* file = fopen(filename, "r");
	char buffer[256];
	//while(f)
}

void complete_task(char* filename, int number)
{
    move_line(filename, "done.txt", number);
    printf("Task #%d complete.\n", number);
}

int main(int argc, char* argv[]){
    // TODO: optionally compile in custom argument parser.
    if (argc > 1){
        if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "add") == 0){
            add_task("todo.txt", argv[2]);
        } else if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "remove")){
            remove_line("todo.txt", "todo.txt~", atoi(argv[2]));
        } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "done")){
            complete_task("todo.txt", atoi(argv[2]));
        } 
        
        else if (strcmp(argv[1], "-l") == 0){
            if (argc = 3) 
	            //list_tasks_matching("todo.txt", argv[2]);
                list_tasks("todo.txt");
            }
    } else { 
        list_tasks("todo.txt");
    }
    return 0;
}
