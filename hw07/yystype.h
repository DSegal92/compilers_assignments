/*******************************************************************************
*
* FILE:		yystype.h for calculator program page 292
*
* DESC:		EECS 337 Assignment 7
*
* AUTHOR:	dls148
*
* DATE:		October 16, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/
#ifndef	YYSTYPE_H
#define	YYSTYPE_H	1

/*
 *	for debugging
 */
#define	YYDEBUG	1
/*
 *	define yystype
 */
#ifndef YYSTYPE
#define YYSTYPE double
#endif


/*
 *	lex variables
 */
extern FILE	*yyin;
extern FILE	*yyout;
extern	char	*yytext;
extern	int	yyleng;
extern	int	yynerrs;
extern	int	yydebug; 
extern	YYSTYPE yylval;
extern	int	yyparse();
extern  void	yyerror( char *);
#endif
