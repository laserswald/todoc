/*
 * strlib.c is part of cligraph.
 * 
 * cligraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * cligraph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cligraph.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	char tmpbuff[end-strt+2];

	//extract the chars from expr
	strncpy(tmpbuff,expr+strt,end-strt+1);
	tmpbuff[end-strt+1] = '\0';
	
	strncpy(buff,tmpbuff,end-strt+2);
	return buff;
}
