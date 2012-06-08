CC = tcc

all: todo.exe

todo.exe: src/todo.c textdb.o
	$(CC) -o todo.exe src/todo.c textdb.o
	
textdb.o: src/textdb.c

task_test.exe: src/task.c task.h proto/task_test.c
	$(CC) -o task_test.exe src/task.c task.h proto/task_test.c -lseatest
