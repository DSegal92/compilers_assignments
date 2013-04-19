/*******************************************************************************
*
* FILE:		Echo.c
*
* DESC:		EECS 337 Homework Assignment 1
*
* AUTHOR:	dls148
*
* DATE:		August 28, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/

#include	<stdio.h>
/*
 *	main program
 */

int	main( int argc, char *argv[])
{
	#define START 0
	#define SLASH1 1
	#define SLASH2 2
	int c;
	int state;
// while input character from stdin does not equal end of file (-1)
	while(( c = getchar()) != EOF){
		if (state == START){
			if (c == '/'){
				state = SLASH1;
			}
			else {
				putchar(c); // put the charater to the stdout
			}
		}
		else if (state == SLASH1){
			if (c == '/'){
				state = SLASH2;
			}
			else {
				state = START;
				putchar('/');
				putchar(c);
			}
		}
		else if (state == SLASH2){
			if (c == '\n'){
				state = START;
				putchar(c);
			}
		}
		
	}
	 //Test Comment
	return 0;
}

