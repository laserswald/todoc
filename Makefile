# Skeleton Medium-sized Makefile for C programs.
#
# by Ben Davenport-Ray

BINNAME=todoc
# Major, minor, build number
VERSION=0.2.6

CC=gcc

BINDIR=bin
LIBNAME=lib$(BINNAME)

DYNLIB=$(BINNAME).dll
STATLIB=$(LIBNAME).a
TESTPRG=$(BINNAME)_test
EXECUTABLE=$(BINNAME)
SONAME=$(LIBNAME).so.$(VERSION)

PKGNAME=$(BINNAME)-$(VERSION)

MODULES=

# Source file gathering.
SOURCE=*.c
SRCDIR=src
SRCS:=$(wildcard $(SRCDIR)/$(SOURCE))

INCLUDE=include

OBJECT=$(SRCS:.c=.o)
OBJDIR=obj
OBJS:=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(OBJECT))
LIBOBJS:=$(filter-out obj/todo.o,$(OBJS))

CFLAGS= -std=c99 -Wall -I$(INCLUDE) -g 
LDFLAGS= -g -lm -L. -ltodoc 
LFLAGS= -shared -Wl,-soname,$(SONAME)

TESTDIR=test
TESTSRC:=$(wildcard $(TESTDIR)/$(SOURCE))
TESTFLAGS=

all: build check

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DYNLIB): $(LIBOBJS)
	$(CC) $(LFLAGS) $^ -o $(DYNLIB) 

$(STATLIB): $(LIBOBJS)
	ar rcs $@ $^

$(TESTPRG): $(TESTSRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

build: setup $(STATLIB) $(EXECUTABLE) $(TESTPRG)

rebuild: clean build

clean: 
	rm -r $(OBJDIR)
	rm  $(STATLIB)
	rm  $(TESTPRG)
	rm  $(EXECUTABLE)

dist:
	tar -cvaf $(PKGNAME).tar.gz $(SRCS) $(INCLUDE)/*.h $(TESTSRC) test/*.h README.mkdn Makefile

distexec:
	$(ZIP) $(PKGNAME)-win32.zip README.md $(EXECUTABLE)

check: $(TESTPRG)
	exec ./$(TESTPRG)

setup:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)

install: $(EXECUTABLE)
	install $(EXECUTABLE) /usr/bin

uninstall:
	rm /usr/bin/$(EXECUTABLE)

.PHONY: all build rebuild clean dist distexec check install uninstall setup
