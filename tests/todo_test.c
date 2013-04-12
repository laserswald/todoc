
#include "seatest.h"

//void task_fixture();
//void tasklist_fixture();
void linkedlist_fixture();

int main(int argc, char** argv){
    int passed = 0; 
    linkedlist_fixture();
//    if (!run_tests(task_fixture)) passed = 1;
//    if (!run_tests(tasklist_fixture)) passed = 1;
    return passed;
}
