/*******************************************************************************
*
* FILE:		lex.l
*
* DESC:		EECS 337 Assignment 8
* SYNOPSIS:	Scanner for Calculator (page 292)
*
* AUTHOR:	dls148
*
* DATE:		October 30, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/
D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include	"yystype.h"
#include	"y.tab.h"
#include	"quad.c"
#include	"symbol.c"

char *formats[] =
{
	" ",
	"decimal",
	"float",
	"octal",
	"hex",
};

/*
 *	print the symbol table
 */
void	print_symbol_table( void)
{
	SYMBOL_TABLE *st;

	printf( "symbol table: \n");
	for( st = data.st; st; st = st->next)
	{
	     switch( st->type) {
	     case TYPE_IDENTIFIER:
	     	     printf( "index: %d identifier: %s\n", st->index, st->string);
		     break;
	     case TYPE_CONSTANT:
	     	     printf( "index: %d constant: %s format: %s\n", st->index, st->string, formats[st->format]);
		     break;
	     }
	}
	return;
}

/*
 *	install the identifier into the symbol table
 */
int installIDENTIFIER( void)
{
	SYMBOL_TABLE *st;
/*
 *	search for the previous string
 */
	for(st = data.st; st; st = st->next )
	     if( ! strcmp( st->string, yytext))
	     	 return st->index;
/*
 *	create a new entry
 */
	st = new_symbol_table(yytext, yyleng + 1);
	st->next = data.st;
	data.st = st;
	st->type = TYPE_IDENTIFIER;
	return st->index;

}

/*
 *	install the constant into the symbol table
 */
int installCONSTANT( int format)
{
	SYMBOL_TABLE *st;
/*
 *	search for the previous string
 */
	for(st = data.st; st; st = st->next )
	     if( ! strcmp( st->string, yytext))
	     	 return st->index;
/*
 *	create a new entry
 */
	st = new_symbol_table(yytext, yyleng + 1);
	st->next = data.st;
	data.st = st;
	st->format = format;
	st->type = TYPE_CONSTANT;
	return st->index;


}

%}

%%

"if"			{ return (IF); }
"else"			{ return (ELSE); }
"$"			{ return -1; /* EOF */ }
[\n]			{ return( '\n'); /* return cr */ }
{L}({L}|{D})*		{ yylval.index = (int) installIDENTIFIER(); return( IDENTIFIER); }
0[xX]{H}+{IS}?		{ yylval.index = (int) installCONSTANT( FORMAT_HEX); return( CONSTANT); }
0{D}+{IS}?		{ yylval.index = (int) installCONSTANT( FORMAT_OCTAL); return( CONSTANT); }
{D}+{IS}?		{ yylval.index = (int) installCONSTANT( FORMAT_DECIMAL); return( CONSTANT); }
{D}+{E}{FS}?		{ yylval.index = (int) installCONSTANT( FORMAT_FLOAT); return( CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ yylval.index = (int) installCONSTANT( FORMAT_FLOAT); return( CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ yylval.index = (int) installCONSTANT( FORMAT_FLOAT); return( CONSTANT); }
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

