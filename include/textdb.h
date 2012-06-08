#ifndef TEXTDATABASE
#define TEXTDATABASE

#include <stdio.h>
#include <string.h>

int copy_lines_except(FILE* source, FILE* dest, int number);
FILE* filecopy(FILE* filename, char* copyname);
int remove_line(char* filename, char* tempname, int number);

#endif