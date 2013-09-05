// Speedunit.h
/*  Speedunit is a basic automated testing suite based on Minunit by
    Jera Design (jera.com). I lifted some of this code from Jera, some 
    from Zed Shaw (learncodethehardway.org), and some of the ideas from 
    seatest (seatest.googlecode.com).

    I made this because other minimalist testing suites are too wordy. 
    Speedunit is designed to be used in IDEs and editors. It allows the dev
    to be as minimalistic as possible.

    Speedunit is liscenced under the DWTFYW Liscence. Effectively, I don't care
    at all about what you do to this. Just be nice and say the above, kay?
*/
#ifndef __SPEEDUNIT
#define __SPEEDUNIT
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dbg.h"

int tests_run;
int tests_failed;

#define sp_pfail(message) do { fprintf(stderr, "fail (%s:%d): %s\n", __FILE__, __LINE__, message); tests_failed++; } while (0);

#define sp_assert(a, message) if (!(a)) sp_pfail(message)

#define sp_streql(str, ing, message) sp_assert(strcmp(str, ing) == 0, message)

#define sp_suite_start() 

#define sp_run_test(test) printf("."); \
    test(); tests_run++

#define sp_run_suite(name) \
    debug("Running test suite: %s", "" #name);\
    name(); \
    puts(""); \
    if (tests_failed != 0) {\
        puts("FAILED");\
    } \
    else { \
        puts("PASSED"); \
    } \
    printf("Tests run: %d\n", tests_run);
#endif
