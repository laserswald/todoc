CC = gcc
CFLAGS = -g -I./include

sources = todo.c task.c tasklist.c filter.c
sourcepath = src
srcs = $(patsubst %,$(sourcepath)/%,$(sources))

objects = $(patsubst %.c,%.o,$(sources))
objectpath = obj
objs = $(patsubst %,$(objectpath)/%,$(objects))

binary = todo

all: setup $(binary) todo_test 

$(binary): $(objs)
	$(CC) -o $(binary) $^ -I./include
	
$(objectpath)/%.o: src/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

todo_test: src/task.c include/task.h tests/todo_test.c tests/seatest.c tests/taskTester.c
	$(CC) -o task_test.exe $^ $(CFLAGS) -I./tests

clean: 
	rm $(objs)

.PHONY: setup clean rebuild dist

rebuild: clean all

dist:
	tar -czvf todoc-0.0.1.tar.gz $(srcs) include/*.h makefile README.mkdn
	zip todoc-dev.zip src include makefile README.mkdn
setup: 
	mkdir -p $(objectpath)
