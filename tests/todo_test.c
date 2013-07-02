

void task_fixture();
//void tasklist_fixture();
void linkedlist_fixture();

int main(int argc, char** argv){
    int passed = 0; 
    linkedlist_fixture();
    task_fixture();
    return passed;
}
