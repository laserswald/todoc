/*
 * strlib.h 
 *
 * AUTHOR: Noah Harvey
 *
 * VERSION: v0.0.1
 *
 * DESCRIPTION: extensions of string.h
 */

#ifndef __STRLIB
#define __STRLIB

/*
 * FUNCTION: strsub
 * 
 * DESCRIPTION: fetches the substring found between the given indeces
 *
 * PARAMETERS: char* expr, size_t strt, size_t end, char* buff
 *
 * RETURNS: char* - buffer containing substring. NULL is returned if error occurs. 
 *
 * NOTE: if buff is not sized properly then a buffer overflow can occur (this string makes use of 
 * strcpy).
 *
 */
char* strsub(char* expr, size_t strt, size_t end, char* buff);

#endif 
