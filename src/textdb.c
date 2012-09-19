#include "textdb.h"

FILE* filecopy(FILE* file, char* copyname){
    
    FILE *temp = fopen(copyname, "w+");
    char buffer[100];
    while(fgets(buffer, 100, file) != NULL){
        fputs(buffer, temp);
    }
    return temp;
}

int copy_lines_except(FILE* source, FILE* dest, int number){
    int line_no = 0;
    char buffer[100];
    while (fgets(buffer, 100, source) != NULL){
        if (number != line_no){
            fputs(buffer, dest);
        }
        line_no++;
    }
}

int remove_line(char* filename, char* tempname, int line){
    FILE *source, *dest;
    if ((source = fopen(filename, "r")) == NULL){
        printf("File %s could not be opened.\n", filename);
        return 1;
    }
    dest = filecopy(source, tempname);
    
    freopen(filename, "w", source);
    freopen(tempname, "r", dest);
    
    copy_lines_except(dest, source, line);
    return 0;
}
