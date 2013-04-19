/*******************************************************************************
*
* FILE:		yacc.y 
*
* DESC:		EECS 337 Assignment 8
* SYNOPSIS:	Calculator (page 292)
*
* AUTHOR:	dls148
*
* DATE:		October 30, 2012
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

%token IDENTIFIER
%token CONSTANT

%left '|'
%left '^'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%right UMINUS UPLUS '~' /* supplies precedence for unary minus */


%% 	/* beginning of rules section */

lines	: lines expr '\n' 
	{
/*
 *	print the quad list
 */
		print_quad_list( $2.quad );
/*
 *	free the quad list
 */
		free_quad_list( $2.quad);
	}
	| lines error '\n' { data.errors++, yyerror(" reenter previous line: "); yyerrok; }
	| /* empty */
	;
expr
	: expr '+' expr
	{ 
		$$.quad = new_quad1( '+', $1.quad, $3.quad);
	}
	| expr '-' expr	
	{ 
		$$.quad = new_quad1( '-', $1.quad, $3.quad);
	}
	| expr '*' expr	
	{ 
		$$.quad = new_quad1( '*', $1.quad, $3.quad);
	}
	| expr '/' expr	
	{ 
		$$.quad = new_quad1( '/', $1.quad, $3.quad);
	}
	| expr '|' expr	
	{
		$$.quad = new_quad1( '|', $1.quad, $3.quad);
	}
	| expr '^' expr	
	{
		$$.quad = new_quad1( '^', $1.quad, $3.quad);
	}
	| expr '&' expr	
	{
		$$.quad = new_quad1( '&', $1.quad, $3.quad);
	}
	| expr '%' expr	
	{
		$$.quad = new_quad1( '%', $1.quad, $3.quad);
	}
	| '(' expr ')'	
	{
		$$.quad = $2.quad;
	}
	| '~' expr 
	{
		$$.quad = new_quad2( '~', $2.quad);
	}
	| '-' expr %prec UMINUS 
	{
		$$.quad = new_quad2( UMINUS, $2.quad);
	}
	| '+' expr %prec UPLUS
	{
		$$.quad = new_quad2( UPLUS, $2.quad);
	}
	| constant
	{
		$$.quad = new_quad3( '=', $1.index);
	}
	| identifier
	{
		$$.quad = new_quad3( '=', $1.index);
	}
	;

constant	: CONSTANT
		;
identifier	: IDENTIFIER
		;

%%
/*
 *	start of post C programs
 */

void	yyerror( char *s)
{
	printf( "%s\n", s);
}

