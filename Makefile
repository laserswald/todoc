CFLAGS= --std=c11

all: todoc

tests/test_suite: tests/task_test.o tests/tasklist_test.o tests/date_test.o tests/todo_test.o

todoc: todoc.o task.o tasklist.o date.o bstrlib.o dllist.o

clean:
	rm *.o
	rm todoc

.PHONY: clean
