/*******************************************************************************
*
* FILE:		yacc.y 
*
* DESC:		EECS 337 Assignment 7
* SYNOPSIS:	Calculator (page 292)
*
* AUTHOR:	dls148
*
* DATE:		October 16, 2012
*
* AUTHOR:	dls148
*
* EDIT HISTORY:	
*
*******************************************************************************/
%{
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "yystype.h"
#include "y.tab.h"

%}

%start lines

%token NUMBER

%left '+' '-'
%left '*' '/' 
%right UMINUS /* supplies precedence for unary minus */

%% 	/* beginning of rules section */

lines	: lines expr '\n' { printf("%g\n", $2); }
	| lines error '\n' { yyerror(" reenter previous line: "); yyerrok; }
	| /* empty */
	;
expr
	: expr '+' expr	{ $$ = $1 + $3;	}
	| expr '-' expr	{ $$ = $1 - $3;	}
	| expr '*' expr	{ $$ = $1 * $3;	}
	| expr '/' expr	{ $$ = $1 / $3;	}
	| '(' expr ')'	{ $$ = $2; }
	| '-' expr %prec UMINUS { $$ = - $2; }
	| number
	;

number	: NUMBER
	;
%%
/*
 *	start of post C programs
 */

void	yyerror( char *s)
{
	printf( "%s\n", s);
}

