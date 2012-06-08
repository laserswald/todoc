FILE* filecopy(FILE* file, char* copyname){

	FILE *temp = fopen(copyname, "w+");
	char buffer[100];
	while(fgets(buffer, 100, file) != NULL){
		fputs(buffer, temp);
	}
	return temp;
}

