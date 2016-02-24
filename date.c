#include <stdlib.h>
#include "date.h"

date* date_new(int year, int month, int day){
    date* d = malloc(sizeof(date));
    // TODO: check if malloc died.
    d->year = year; 
    d->month = month;
    d->day = day; 
    return d;
}

int date_free(date* d){
    free(d);
    return 0;
}

int date_cmp(date* a, date* b){
    if (!a) return -1;
    if (!b) return 1;
    // See, we COULD do it with memcmp() but this is more modular, though more verbose.
    if (a->year == b->year){
        if (a->month == b->month){
            if (a->day == b->day) return 0;
            else if (a->day > b->day) return 1;
            else return -1;
        } else if (a->month > b->month) return 1;
        else return -1;
    } else if (a->year > b->year) return 1;
    else return -1;
}
