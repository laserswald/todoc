CC = gcc
CFLAGS = -g -I./include
sources = todo.c task.c tasklist.c
sourcepath = src
srcs = $(patsubst %,$(sourcepath)/%,$(sources))

objects = $(patsubst %.c,%.o,$(sources))
objectpath = obj
objs = $(patsubst %,$(objectpath)/%,$(objects))

binary = todoc

all: setup $(binary) todo_test 

$(binary): $(objs)
	$(CC) -o $(binary) $^ -I./include
	
$(objectpath)/%.o: src/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

todo_test: src/task.c include/task.h src/tasklist.c include/tasklist.h tests/todo_test.c tests/seatest.c tests/task_test.c tests/tasklist_test.c
	$(CC) -o task_test.exe $^ $(CFLAGS) -I./tests

clean: 
	rm $(objs)

.PHONY: setup clean rebuild dist

rebuild: clean all

dist:
	tar -czvf todoc-0.2.0.tar.gz $(srcs) include/*.h Makefile SConstruct README.mkdn
	zip todoc-dev.zip src include Makefile SConstruct README.mkdn
setup: 
	mkdir -p $(objectpath)
