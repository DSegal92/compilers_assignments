/*******************************************************************************
*
* FILE:		relop.l
*
* DESC:		EECS 337 Assignment 4
*
* AUTHOR:	dls148
*
* DATE:		September 25, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/

%{

#include	"yystype.h"

/*
 *	install the identifer into the symbol table
 */
char installID( void)
{
	int cur_sym = ++data.count; 
	if (cur_sym >= MAX_SYMBOLS) 
		return 0; 
	data.st[cur_sym].type = TYPE_IDENTIFIER; 
	strncpy(data.st[cur_sym].string, yytext, yyleng); 
	return ID; 
}

/*
 *	install the constant into the symbol table
 */
int installNum( void)
{
	int cur_sym = ++data.count; 
	if (cur_sym >= MAX_SYMBOLS) 
		return 0; 
	data.st[cur_sym].type = TYPE_CONSTANT; 
	data.st[cur_sym].format = NUM_FORMAT; 
	strncpy(data.st[cur_sym].string, yytext, yyleng); 
	return NUMBER; 
}

/*
 *	print the operands and relational operator
 */
void	print_relational_expr( int expr1, int relop, int expr2)
{
	printf( "expr1: %d relop: %d expr2: %s\n", expr1, relop, yytext);
	return;
}

/*
 *	print the symbol table identifier or constant/type/format 
 */
void	print_symbol_table( void)
{
	printf( "symbol table: \n");
	return;
}

%}

/* regular definitions */
delim	   [ \t\n]
ws	   {delim}+
letter	   [A-Za-z]
digit	   [0-9]
id	   {letter}({letter}|{digit})*
number	   {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws}		{/* no action and no return */}
if		{ return( IF);}
then		{ return( THEN);}
else		{ return( ELSE);}
{id}		{ yylval = (int) installID(); return( ID); }
{number}	{ yylval = (int) installNum(); return( NUMBER); }
"<"		{ yylval = LT; return( RELOP);}
"<="		{ yylval = LE; return( RELOP);}
"="		{ yylval = EQ; return( RELOP);}
"<>"		{ yylval = NE; return( RELOP);}
">"		{ yylval = GT; return( RELOP);}
">="		{ yylval = GE; return( RELOP);}

%%

/*
 *	yywrap function
 */
int	yywrap( void)
{
	return(1);
}
