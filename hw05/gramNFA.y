/*******************************************************************************
*
* FILE:		gramNFA.y
*
* DESC:		EECS 337 Assignment 5
*
* AUTHOR:	dls148
*
* DATE:		October 2, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/
%{

#include	"yystype.h"

%}

%start line

%%

// NFA 
line		: A0 '\n'
		| line A0 '\n'
		;
A0		: aletter A0
		| bletter A0
        | aletter A1
        ;
A1		: aletter A2
        | bletter A2
        ;
A2    : aletter A3
        | bletter A3
        ;
A3      : /*empty*/
        ;

aletter		: 'a'
		;
bletter		: 'b'
		;

%%

void	yyerror( char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", data.column, "^", data.column, s);
}
