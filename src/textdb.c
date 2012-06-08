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

int copy_single_line(FILE* source, FILE* dest, int number)
{
    int line = 0;
    char buffer[256];
    while(fgets(buffer, 256, source)!=NULL){
        if (number = line){
            fputs(buffer, dest);
        }    
        line++;
    }
}

int remove_line(char* filename, char* tempname, int line){
	FILE *source, *dest;
	if ((source = fopen(filename, "r")) == NULL){
		printf("File %s could not be opened.\n", filename);
	}
	dest = filecopy(source, tempname);
	
	freopen(filename, "w", source);
	freopen(tempname, "r", dest);
	
	copy_lines_except(dest, source, line);

    fclose(source);
    fclose(dest);
}

int move_line(char* filename, char* destination, int line){
    FILE *source, *dest;
    if ((source = fopen(filename, "r")) == NULL){
		printf("File %s could not be opened.\n", filename);
	    return -1;
    }
    if ((dest = fopen(destination, "w")) == NULL){
		printf("File %s could not be opened.\n", destination);
        return -1;
	}
    copy_single_line(source, dest, line);
    fclose(source);
    fclose(dest);
    puts("Removing line");
    remove_line(filename, "move.tmp", line);
    remove("move.tmp");
}
