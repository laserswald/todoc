/*
 * strlib.c 
 *
 * AUTHOR: Noah Harvey
 *
 * VERSION: v0.0.1
 *
 * DESCRIPTION: definition of strlib functions 
 */

#include <string.h>
#include "str.h"

char* strsub(char* expr, size_t strt, size_t end, char* buff)
{
	if(!expr || !buff) return NULL;
	
	if(strt < 0 || strt > end || strt > strlen(expr)-1) return NULL;
	if(end < 0|| end < strt || end > strlen(expr)-1) return NULL;

	//use a temp buff to allow buff == expr
	char tmpbuff[end-strt+1];

	//extract the chars from expr
	strncpy(tmpbuff,expr+strt,end-strt+1);
	tmpbuff[end-strt+1] = '\0';
	
	strncpy(buff,tmpbuff,end-strt+2);
	return buff;
}
