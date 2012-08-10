CC = gcc
CFLAGS = -g -I./include

sources = todo.c textdb.c filter.c
sourcepath = src
srcs = $(patsubst %,$(sourcepath)/%,$(sources))

<<<<<<< .merge_file_XC3DTe
todo.exe: src/todo.c task.o tasklist.o
	$(CC) -o todo.exe src/todo.c textdb.o -I./include
	
task.o: src/task.c
	$(CC) -o task.o src/task.c src/tasklist.c -I./include  
	
tasklist.o: src/tasklist.c
	$(CC) -o tasklist.o src/tasklist.c -I./include  

=======
objects = $(patsubst %.c,%.o,$(sources))
objectpath = obj
objs = $(patsubst %,$(objectpath)/%,$(objects))

binary = todo

all: setup $(binary)

$(binary): $(objs)
	$(CC) -o $(binary) $^ -I./include
	
$(objectpath)/%.o: src/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)
>>>>>>> .merge_file_7pf0Oc

task_test.exe: src/task.c task.h proto/task_test.c
	$(CC) -o task_test.exe src/task.c task.h proto/task_test.c -lseatest

clean: 
	rm $(objs)

.PHONY: setup clean rebuild dist

rebuild: clean all

dist:
	tar -czvf todoc-0.0.1.tar.gz $(srcs) include/*.h makefile README.mkdn
	zip todoc-dev.zip src include makefile README.mkdn
setup: 
	mkdir -p $(objectpath)
