/*******************************************************************************
*
* FILE:		gram.y
*
* DESC:		EECS 337 Assignment 3
*
* AUTHOR:	dls148
*
* DATE:		September 18, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/
%{

#include	"yystype.h"
int		factor;

%}

%token T_UNIVERSE

%start everything

%%

/*
 *	the smallest compiler, parsers any one character 
 */
everything	: T_UNIVERSE
		{
#ifdef	YYDEBUG
			if( IS_FLAGS_DEBUG( data.flags))
			  printf( "character: $1=%c\n", (char)$1);
#endif
		}
		;
%%

void	yyerror( char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", data.column, "^", data.column, s);
}
