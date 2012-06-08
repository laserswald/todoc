CC = gcc

all: todo.exe

todo.exe: src/todo.c task.o tasklist.o
	$(CC) -o todo.exe src/todo.c textdb.o -I./include
	
task.o: src/task.c
	$(CC) -o task.o src/task.c src/tasklist.c -I./include  
	
tasklist.o: src/tasklist.c
	$(CC) -o tasklist.o src/tasklist.c -I./include  


task_test.exe: src/task.c task.h proto/task_test.c
	$(CC) -o task_test.exe src/task.c task.h proto/task_test.c -lseatest

clean: 
	rm textdb.o

.PHONY: clean rebuild

rebuild: clean all

