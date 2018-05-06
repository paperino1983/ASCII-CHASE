/*****************************************************************************/
/*                                                                           */
/*                                		                                     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2017      Fabrizio Caruso                                  		     */
/*                					                                         */
/*              				                                             */
/* EMail:        Fabrizio_Caruso@hotmail.com                                 */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/

#ifndef _KC_CONIO_IMPLEMENTATION
#define _KC_CONIO_IMPLEMENTATION
	#include <stdio.h>

	//printf("%c%c%c%c",27,'=',y+32,x+32);
	// 		printf("\33[%c;%cH",y+32,x+32); \
	
	#define gotoxy(x,y) do \
		{ \
		printf("\1B%c%c",y+0x80, x+0x80); \
		\
		} while(0)
		
	// printf("%c%c",27,'*')	
	#define clrscr() printf("\0C");

	#define cprintf printf
			
	// 		printf("%c%c", 27,'2');
	#define cputc(c) do \
		{ \
		fputc_cons(c); \
		} while(0)
	
	#define cgetc() getk()

	#define textcolor 

	
	#define COLOR_BLACK 0	
	#define COLOR_BLUE 1

	#define COLOR_RED 2
	#define COLOR_MAGENTA 3
	
	#define COLOR_GREEN 4
	#define COLOR_CYAN 5
	
	#define COLOR_YELLOW 6
	#define COLOR_WHITE 7
	
#endif // KC_CONIO_IMPLEMENTATION

