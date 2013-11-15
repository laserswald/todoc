
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"
#include "argparse.h"

Argument* new_argument(){
    Argument* arg = (Argument*)malloc(sizeof(Argument));
    arg->name = NULL;
    arg->option = NULL;
    return arg;
}

ArgElement* new_argelem(Argument* arg){
    ArgElement* n = (ArgElement*)malloc(sizeof(ArgElement));
    if (n == NULL) return NULL;
    n->arg = arg;
    n->next = NULL;
    return n;
}

void free_argument(Argument *arg){
    free(arg->name);
    free(arg->option);
    free(arg);
}

/* Recursively free argelems. */
void free_argelems(ArgElement *element){
    if (element == NULL) return;
    free_argument(element->arg);
    free_argelems(element->next);
    free(element);
}

/* Free an argument list. */
void ArgList_free(ArgList *list){
    free_argelems(list->head);
    free(list);
}


int arglist_add(ArgList* l, Argument* a){
    // TODO: finish this
    ArgElement* el = new_argelem(a);
    if (el == NULL) return -1;
    ArgElement* slider = l->head;
    if (slider == NULL) {
        l->head = el;
        return 0;
    }
    while (slider->next != NULL){slider = slider->next;}
    slider->next = el;
    l->length = l->length+1;
    return 0;
}

/* Create a list of arguments from an array of strings. */
ArgList *ArgList_make(int argc, char** argv){
    ArgList *list = (ArgList*) malloc(sizeof (ArgList));
    list->length = 0;
    list->head = NULL;
    
    Argument* currentarg = NULL;
    int i;
    /* Check each item in the vector. */
    for (i = 0; i<argc; i++){
        
        if (argv[i][0] == '-'){
            // It's some kind of option.
            if (currentarg) arglist_add(list, currentarg);
            // TODO: make this into a function.
            // TODO: make this handle "-s=opt" notation
            currentarg = new_argument();
            currentarg->name = strdup(argv[i]);
        } else {
            currentarg->option = strdup(argv[i]);
        }
    }
    if (currentarg) arglist_add(list, currentarg);
    return (list);
}

