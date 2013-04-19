/*******************************************************************************
*
* FILE:		yacc.y 
*
* DESC:		EECS 337 Assignment 11
* SYNOPSIS:	Calculator (page 292)
*
* AUTHOR:	dls148
*
* DATE:		November 20, 2012
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
#include "codegen.c"
#include "codegen2.c"

TUPLE	 *tuple_list;
%}

%start file

%token IDENTIFIER
%token CONSTANT
%token IF
%token ELSE
%token LABEL
%token GOTO
%token CHAR
%token SHORT
%token INT
%token LONG

%left '|'
%left '^'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%right UMINUS UPLUS '~' /* supplies precedence for unary minus */


%% 	/* beginning of rules section */

file	: stmts
	{
/*
 *	print the quad list
 */
		print_quad_list( $1.quad );
/*
 *	generate the tuple from quad list
 */
		tuple_list = generate_quad_2_tuple( $1.quad);
/*
 *	free the quad list
 */
		free_quad_list( $1.quad);
/*
 *	call the code generator
 */
		code_generator_pic16f84( tuple_list);
	}
	;
stmts	: stmts stmt
	{
		$$.quad = end_quad_list( $1.quad);
		if( $$.quad)
		{
		    $$.quad->next = $2.quad;
		    $$.quad = $1.quad;
		}
		else
		    $$.quad = $2.quad;
	}
	| stmt
	;
stmt	: IF '(' expr ')' stmt
	{
		$$.quad = new_quad5( IF, $3.quad, $5.quad);
	}
	| IF '(' expr ')' stmt ELSE stmt
	{
		$$.quad = new_quad5E( IF, $3.quad, $5.quad, $7.quad);
	}
	| identifier '=' expr ';'
	{
		$$.quad = new_quad3A( '=', $1.index, $3.quad);
	}
	| identifier '[' expr ']' '=' expr ';'
	{
		$$.quad = new_quad3ARRAY( '=', $1.index, $3.quad, $6.quad);
	}
	| type identifier ';'
	{
		$$.quad = new_symbol( $1.index, $2.index);
	}
	| type identifier '[' constant ']' ';'
	{
		$$.quad = new_symbolARRAY( $1.index, $2.index, $4.index);
	}
	;
type	: CHAR
	| SHORT
	| INT
	| LONG
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
	| identifier '[' expr ']'
	{
		$$.quad = new_quad3E( ']', $1.index, $3.quad);
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

