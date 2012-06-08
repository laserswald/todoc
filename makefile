CC = gcc

all: todo.exe

todo.exe: src/todo.c textdb.o
	$(CC) -o todo.exe src/todo.c textdb.o -I./include
	
textdb.o: src/textdb.c
	$(CC) -c -o textdb.o src/textdb.c -I./include  

task_test.exe: src/task.c task.h proto/task_test.c
	$(CC) -o task_test.exe src/task.c task.h proto/task_test.c -lseatest

clean: 
	rm textdb.o

.PHONY: clean rebuild

rebuild: clean all

