/*******************************************************************************
*
* FILE:		ifthen.y
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

%}

%token IF
%token THEN
%token ELSE
%token ID
%token NUMBER
%token RELOP
%token LT
%token LE
%token EQ
%token NE
%token GT
%token GE

%start file

%%

primary_expr
	: ID
	| NUMBER
	;

relational_expr
	: primary_expr RELOP primary_expr
	{
		print_relational_expr( $1, $2, $3);
	}
	;

if_statement
	: IF relational_expr THEN 
	| IF relational_expr THEN ELSE
	;

file	: if_statement
	| file if_statement
	;
%%

void	yyerror( char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", data.column, "^", data.column, s);
}
