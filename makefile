CC = gcc
CFLAGS = -I./include

sources = todo.c textdb.c filter.c
sourcepath = src
srcs = $(patsubst %,$(sourcepath)/%,$(sources))

objects = $(patsubst %.c,%.o,$(sources))
objectpath = obj
objs = $(patsubst %,$(objectpath)/%,$(objects))

binary = todo

all: setup $(binary)

$(binary): $(objs)
	$(CC) -o $(binary) $^ -I./include
	
$(objectpath)/%.o: src/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

task_test.exe: src/task.c task.h proto/task_test.c
	$(CC) -o task_test.exe src/task.c task.h proto/task_test.c -lseatest

clean: 
	rm textdb.o filter.o

.PHONY: setup clean rebuild dist

rebuild: clean all

dist:
	tar -czvf todoc-0.0.1.tar.gz $(srcs) include/*.h makefile README.mkdn
	zip todoc-dev.zip src include makefile README.mkdn
setup: 
	mkdir -p $(objectpath)
