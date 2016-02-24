#include "util/speedunit.h"

sp_suite(date_suite);
sp_suite(task_fixture);
sp_suite(tasklist_fixture);

int main(int argc, char** argv){
    int passed = 0; 
//    sp_run_suite(date_suite); 
    sp_run_suite(task_fixture);
//    sp_run_suite(tasklist_fixture);
    return passed;
}
