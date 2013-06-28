CC = gcc
CFLAGS = -g -I./include
sources = todo.c task.c tasklist.c linkedlist.c
sourcepath = src
srcs = $(patsubst %,$(sourcepath)/%,$(sources))

objects = $(patsubst %.c,%.o,$(sources))
objectpath = obj
objs = $(patsubst %,$(objectpath)/%,$(objects))

binary = todoc

all: setup $(binary) todo_test run_test

$(binary): $(objs)
	$(CC) -o $(binary) $^ -I./include
	
$(objectpath)/%.o: src/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

todo_test: src/task.c include/task.h src/tasklist.c include/tasklist.h tests/todo_test.c tests/seatest.c tests/task_test.c tests/lltest.c include/linkedlist.h src/linkedlist.c
	$(CC) -o todo_test $^ $(CFLAGS) -I./tests

clean: 
	rm $(objs)

.PHONY: setup clean rebuild dist

rebuild: clean all

dist:
	tar -czvf todoc-0.2.tar.gz $(srcs) include tests Makefile SConstruct README.mkdn

setup: 
	mkdir -p $(objectpath)

run_test: todo_test
	exec ./todo_test
