/*******************************************************************************
*
* FILE:		scan.l
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

%%
[a]	{ yylval = (int) yytext[0]; return yytext[ 0];  }
[b]	{ yylval = (int) yytext[0]; return yytext[ 0]; }
[\n]	{ yylval = (int) yytext[0]; return yytext[ 0]; }
.	{ return(0); }

%%
/*
 * resync the parser with a syntax error
 */
void yysync( void)
{
int c;
data.errors++;
while (( c = getc( yyin )) != EOF)
{
if( c == '\n')
{
    unput( c);
    break;
}
}
}

/*
 *	yywrap function
 */
int	yywrap( void)
{
	return(1);
}

