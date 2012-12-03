
#include <stdlib.h>
#include <string.h>

#include <filter.h>

int isIn(char* string, char* search){
    if (strstr(string, search) == NULL){
        return 0;
    } else {
        return 1;
    }
}
