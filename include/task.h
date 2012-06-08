#ifndef TASK
#define TASK

typedef struct task{
	char* description;
	char** tags;
	int taglen;
	char priority;
	
}Task;

Task* Task_new();

void Task_append(Task* t, char* string);

int Task_has_project(Task* t, char* project);
int Task_has_context(Task* t, char* context);

char* Task_dump(Task* t);

void Task_print(Task* t);
#endif