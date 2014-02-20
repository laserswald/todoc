// Ben Davenport-Ray's argument parser. 

#ifndef __ARGPARSE__
#define __ARGPARSE__

// Holds the name of the argument and an option.
typedef struct Argument {
    char *name;
    char *option;
}Argument;

// A linked list of these elements.
typedef struct ArgElement {
    Argument *arg;
    struct ArgElement *next;
}ArgElement;

typedef struct ArgList{
    int length;
    struct ArgElement *head;
}ArgList;

// Parse a list of command line arguments.
ArgList* ArgList_make(int argc, char** argv);

// Delete the list of arguments.
void ArgList_free(ArgList* list);

#endif // Argparse
