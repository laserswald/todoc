#ifndef DATE_H

#define DATE_H

#include <time.h>

typedef struct _date {
    int year;
    int month;
    int day;
} date;

// make new date from ints
date* date_new(int year, int month, int day);

// free date info
int date_free(date* d);

// Get a date from tm.
date* datefromtm(struct tm* t);

// Compare two dates. 
// returns negative if a is less than b
//         positive if a is greater than b
//         0 if a and b are same date
int date_cmp(date* a, date* b);

#endif /* end of include guard: DATE_H */
