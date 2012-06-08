#include <stdio.h>
#include <string.h>

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

int remove_line(const char* filename, const char* tempname, int line){
	FILE *source, *dest;
	source = fopen(filename, "r");
	dest = filecopy(source, tempname);
	
	freopen(filename, "w", source);
	freopen(tempname, "r", dest);
	
	copy_lines_except(dest, source, line);
}

int main(){

	
	return 0;
}