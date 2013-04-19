/*******************************************************************************
*
* FILE:		calc.c
*
* DESC:		EECS 337 Assignment 7
*      		Main routine to call the Calculator page 292
*
* AUTHOR:	dls148
*
* DATE:		October 16, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>
#include	"yystype.h"

/*******************************************************************************
 *	main program
 ******************************************************************************/
int	main( int argc, char *argv[])
{
	time_t	t;
/*
 *	print start of test time
 */
	time( &t);
	fprintf( stdout, "for dls148 start time: %s", ctime( &t));
/*
 *	check command line
 */
	if( 1 < argc)
		yydebug = 1;
/*
 *	print the sizeof integers, longs, floats and doubles
 */
	printf( "SIZEOF int: %d long: %d float: %d double: %d\n", (int)sizeof( int), (int)sizeof( long), (int)sizeof( float), (int)sizeof( double));
/*
 *	call the parser
 */
	printf( "Enter calculator expression and $ to exit\n");
	yyparse();
/*
 *	return
 */
	return 0;
}

