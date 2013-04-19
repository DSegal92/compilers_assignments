/*******************************************************************************
*
* FILE:		gramDFA.y
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

// DFA 
line		: A0 '\n'
		| line A0 '\n'
		| error '\n' { yysync(); yyerrok; }
		;
A0		: aletter A1
		| bletter A0
        ;
A1		: aletter A2
        | bletter A5
        ;
A2		: aletter A3
        | bletter A4
        ;
A3		: aletter A3
        | bletter A4
        | /* empty */
        ;
A4		: aletter A6
        | bletter A7
        | /* empty */
        ;
A5		: aletter A6
        | bletter A7
        ;
A6		:bletter A5
        | /* empty */
        ;
A7		: aletter A1
        | bletter A0
        | /* empty */
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
