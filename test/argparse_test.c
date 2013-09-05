#include "stdlib.h"
#include "argparse.h"
#include "speedunit.h"

void no_args(){
    int argc = 0;
    char **argv = NULL;

    ArgList* al = ArgList_make(argc, argv);
    sp_assert(al, "Something is wrong with making an arglist");
    sp_assert(al->length == 0, "Arglist aquired something."); 
    
}

void argparse_fixture(){
    sp_run_test(no_args);
}
