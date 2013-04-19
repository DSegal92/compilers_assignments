/*******************************************************************************
*
* FILE:		yystype.h for ifrelop compiler
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
#ifndef	YYSTYPE_H
#define	YYSTYPE_H	1

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>
#include	"y.tab.h"

/*
 * symbol table
 */
#define SYMBOL_TABLE struct symbol_table
SYMBOL_TABLE
{
#define MAX_STRING 32
char string[ MAX_STRING];
#define TYPE_IDENTIFIER 1
#define TYPE_CONSTANT 2
int type;
#define FORMAT_DECIMAL 1
#define FORMAT_FLOAT 2
#define FORMAT_OCTAL 3
#define FORMAT_HEX 4
int format;

};


/*
 *	define a global data structure
 */
#define	DATA	struct data
DATA
{
	int	column;
	int	flags;
#define	FLAGS_ECHO	0x0001
#define	FLAGS_DEBUG	0x0002
#define	FLAGS_PARSE	0x0004
#define	IS_FLAGS_ECHO(a)	(a & FLAGS_ECHO)	
#define	SET_FLAGS_ECHO(a)	(a |= FLAGS_ECHO)
#define	CLR_FLAGS_ECHO(a)	(a &= ~FLAGS_ECHO)
#define	IS_FLAGS_DEBUG(a)	(a & FLAGS_DEBUG)	
#define	SET_FLAGS_DEBUG(a)	(a |= FLAGS_DEBUG)
#define	CLR_FLAGS_DEBUG(a)	(a &= ~FLAGS_DEBUG)
#define	IS_FLAGS_PARSE(a)	(a & FLAGS_PARSE)	
#define	SET_FLAGS_PARSE(a)	(a |= FLAGS_PARSE)
#define	CLR_FLAGS_PARSE(a)	(a &= ~FLAGS_PARSE)
	/*
 * symbol table
 */
#define MAX_SYMBOLS 16
int count;
SYMBOL_TABLE st[ MAX_SYMBOLS];
};

/*
 *	define for yyparser debugging
 */
#define	YYDEBUG	1
/*
 *	external variables and functions from relop.l
 */
extern FILE	*yyin;
extern FILE	*yyout;
extern	char	*yytext;
extern	int	yyleng;
extern	int	yynerrs;
extern	int	yylval;		/* YYSTYPE */
extern	int	yywrap( void);
extern	void	print_relational_expr( int expr1, int relop, int expr2);
extern	void	print_symbol_table( void);
/*
 *	external variables and functions from iften.y
 */
extern	int	yydebug;
extern	int	yyparse( void);
extern	void	yyerror( char *s);
/*
 *	external variables and functions from main.c
 */
extern	DATA	data;
extern	int	main( int argc, char *argv[]);

#endif
