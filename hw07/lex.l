/*******************************************************************************
*
* FILE:		lex.l
*
* DESC:		EECS 337 Assignment 7
* SYNOPSIS:	Scanner for Calculator (page 292)
*
* AUTHOR:	dls148
*
* DATE:		October 16, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/
D			[0-9]

%{
#include	"yystype.h"
#include	"y.tab.h"

%}

%%

"$"			{ return -1; /* EOF */ }
[\n]			{ return( '\n'); /* return cr */ }
{D}			{ yylval = (double)(yytext[0] - '0'); return( NUMBER); }
[ \t]			{ /* ignore white characters */ }
.			{ return( yytext[ 0]); /* return everything else */ }

%%

/*
 *	yy wrap function	always return NO
 */
yywrap()
{
	return( 1);
}

