#include "task.h"

/* WARNING: Unclean code! */
Task* Task_new(){
	Task* t = (Task*)malloc(sizeof(Task));
	t->description = NULL;
	return t;
}

void Task_parse(Task* t, char* string){
	char* buffer = 
}

/* WARNING: Unclean code! */
void Task_append(Task* t, char* string)
{
	/* Hack: maybe I should make a resize + append function....*/
	int oldlen, newlen;
	oldlen = strlen(t->description);
	newlen = strlen(desc) + oldlen;
	t->description = realloc(t->description, (sizeof(char)*newlen)+1);
	t->description = strcat(t->description, desc);
}

/** Dumps out the current task's data in Todo.txt format.*/
/* WARNING: Unclean code! */
char* 
Task_dump(Task* t)
{
	int dumpsize = 0;
	char* dump;
	dump = (char*)malloc(0+1);
	/* 
	Check if this task has a priority. If so, then put that in there.
	NO priority will be symbolized in this implementation as anything
	that is not an alphabetical character. If it is an alphabetical character, 
	then it is automatically uppercased.
	*/
	
	if (isalpha(t->priority)){
		int newpriority = toupper((int)t->priority);
		dumpsize += 5;
		dump = realloc(dump, sizeof(char*) * dumpsize);
		dump = sprintf("%s (%c)", dump, newpriority);
	}
	
	if (t->description){
		dumpsize += strlen(t->description);
		dump = realloc(dump, sizeof(char*) * dumpsize);
		dump = sprintf(dump, "%s %s", dump, t->description);
	}
	
	return dump;
}

int 
Task_has_keyword(Task* t, char* keyword){
	if (strstr(t->description, keyword) = NULL){
		return 0;
	}
	return 1;
}
