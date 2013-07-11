CC = gcc
CFLAGS = -g -I./include
sources = todo.c task.c tasklist.c linkedlist.c
sourcepath = src
srcs = $(patsubst %,$(sourcepath)/%,$(sources))

objects = $(patsubst %.c,%.o,$(sources))
objectpath = obj
objs = $(patsubst %,$(objectpath)/%,$(objects))

binary = todoc
testbin = todoc_test

all: setup $(binary) $(testbin) run_test

$(binary): $(objs)
	$(CC) -o $(binary) $^ -I./include
	
$(objectpath)/%.o: src/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(testbin): src/task.c include/task.h src/tasklist.c include/tasklist.h tests/todo_test.c tests/tasklist_test.c tests/task_test.c tests/lltest.c include/linkedlist.h src/linkedlist.c
	$(CC) -o $(testbin) $^ $(CFLAGS) -I./tests

clean: 
	rm $(objs) $(binary) $(testbin)

.PHONY: setup clean rebuild dist

rebuild: clean all

dist:
	tar -czvf todoc-0.2.tar.gz $(srcs) include tests Makefile SConstruct README.mkdn

setup: 
	mkdir -p $(objectpath)

run_test: $(testbin)
	exec ./$(testbin)
