#ifndef TASK
#define TASK

struct task_t{
	char* description;
	char priority;	
};

struct task_t* task_new();

void task_setString(struct task_t* t, char* string);
void task_append(struct task_t* t, char* string);

int task_has_project(struct task_t* t, char* project);
int task_has_context(struct task_t* t, char* context);

char* task_dump(struct task_t* t);

void task_print(struct task_t* t);
#endif
