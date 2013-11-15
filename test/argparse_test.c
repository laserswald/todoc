#include "stdlib.h"
#include "argparse.h"
#include "speedunit.h"

void no_args(){
    int argc = 0;
    char **argv = NULL;

    ArgList* al = ArgList_make(argc, argv);
    sp_assert(al, "Something is wrong with making an arglist");
    sp_assert(al->length == 0, "Arglist aquired something."); 
    
    ArgList_free(al);
}

void check_args(int argco, char** argve){
	ArgList* al = ArgList_make(argco, argve);
	ArgElement* index;
    int i;
	for (index = al->head, i = 0; index != NULL; i++, index = index->next){
        sp_streql(index->arg->name, argve[i], "Arguments not inserted.");
	}
	ArgList_free(al);
}

// Checks if it is possible to use one argument.
void no_values(){
	int single_co = 1;
	char *single_ve[] = {"-argument"};
    check_args(single_co, single_ve);

    int many_co = 3;
    char *many_ve[] = {"-a", "-b", "-c"};
    check_args(many_co, many_ve);
}

void arg_with_option()
{
    int count = 2;
    char *vector[] = {"-a", "apple"};    
    ArgList* al = ArgList_make(count, vector);
    ArgElement* index = al->head;
    sp_streql(vector[0], index->arg->name, "Argument name is incorrect");
    sp_streql(vector[1], index->arg->option, "Argument option is incorrect");
}

void argparse_fixture(){
    sp_run_test(no_args);
    sp_run_test(no_values);
    sp_run_test(arg_with_option);
}
