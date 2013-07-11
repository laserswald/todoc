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
#ifndef SPEEDUNIT 
#define SPEEDUNIT
#include <stdio.h>
#include <string.h>

#define sp_pfail(message) do {printf("%s: %d: fail: %s\n", __FILE__, __LINE__, message); } while (0)

#define sp_assert(test, message) do { if (!(test)) sp_pfail(message);} while (0)
#define sp_streql(str, ing, message) sp_assert(strcmp(str, ing) == 0, message)
     
#endif /* SPEEDUNIT */

