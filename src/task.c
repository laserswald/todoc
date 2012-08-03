#include "task.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* WARNING: Unclean code! */
struct task_t* task_new(){
	struct task_t* t = (struct task_t*)malloc(sizeof(struct task_t));
	t->description = NULL;
	return t;
}

void task_setString(struct task_t* t, char* string)
{
    t->description = strdup(string);
}

/* WARNING: Unclean code! */
void task_append(struct task_t* t, char* string)
{
	/* Hack: maybe I should make a resize + append function....*/
	int oldlen, newlen;
	oldlen = strlen(t->description);
	newlen = strlen(string) + oldlen;
	t->description = realloc(t->description, (sizeof(char)*newlen)+1);
	t->description = strcat(t->description, string);
}

/** Dumps out the current task's data in Todo.txt format.*/
/* WARNING: Unclean code! */
char* 
task_dump(struct task_t* t)
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
task_has_keyword(struct task_t* t, char* keyword){
	if (strstr(t->description, keyword) == NULL){
		return 0;
	}
	return 1;
}
