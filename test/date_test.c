#include "date.h"
#include "speedunit.h"

void date_mem_test(){
    date* birthday = date_new(1994, 0, 21);
    sp_assert(birthday, "Birthday is null");

    sp_assert(birthday->year == 1994, "Birthday year is wrong");
    sp_assert(birthday->day == 21, "Birthday date is wrong");
    sp_assert(birthday->month == 0, "Birthday month is wrong");

    date_free(birthday);
}

void date_compare_test(){
    date* new_mill = date_new(2000, 0, 1); 
    date* some_date = date_new(2013, 9, 12);
    sp_assert(date_cmp(new_mill, some_date) < 0, "Dates not ordered correctly");

    date_free(new_mill);    
}


void date_suite(){
    sp_run_test(date_mem_test);
    sp_run_test(date_compare_test);
}
