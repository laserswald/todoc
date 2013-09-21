#include "speedunit.h"

void task_fixture();
void tasklist_fixture();
void linkedlist_fixture();
void argparse_fixture();

int main(int argc, char** argv){
    int passed = 0; 
    sp_run_suite(argparse_fixture);
    sp_run_suite(linkedlist_fixture);
    sp_run_suite(task_fixture);
    sp_run_suite(tasklist_fixture);
    return passed;
}
