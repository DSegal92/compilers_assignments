/*******************************************************************************
*
* FILE:		lex.l
*
* DESC:		EECS 337 Assignment 11
* SYNOPSIS:	Scanner for Calculator (page 292)
*
* AUTHOR:	dls148
*
* DATE:		November 20, 2012
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

char *types[] =
{
	" ",
	"char",
	"short",
	" ",
	"int",
	" ",
	" ",
	" ",
	"long",
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
	     switch( st->type)
	     {
	     case TYPE_IDENTIFIER:
		     if( 1 < st->size)
	     	     	 printf( "index: %d identifier: %s[%d] type: %s\n", st->index, st->string, st->size, types[ st->format]);
		     else
	     	     	 printf( "index: %d identifier: %s type: %s\n", st->index, st->string, types[ st->format]);
		     break;
	     case TYPE_CONSTANT:
	     	     printf( "index: %d constant: %s format: %s\n", st->index, st->string, formats[ st->format]);
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
	for( st = data.st; st; st = st->next)
	     if( ! strcmp( st->string, yytext))
	     	 return st->index;
/*
 *	create a new entry
 */
	st = new_symbol_table( yytext, yyleng + 1);
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
	for( st = data.st; st; st = st->next)
	     if( ! strcmp( st->string, yytext))
	     	 return st->index;
/*
 *	create a new entry
 */
	st = new_symbol_table( yytext, yyleng + 1);
	st->next = data.st;
	data.st = st;
	st->type = TYPE_CONSTANT;
	st->format = format;
	switch( st->format)
	{
	case FORMAT_HEX:
	     sscanf( yytext, "%x", &(st->ivalue));
	     break;
	case FORMAT_OCTAL:
	     sscanf( yytext, "%o", &(st->ivalue));
	     break;
	case FORMAT_DECIMAL:
	     sscanf( yytext, "%d", &(st->ivalue));
	     break;
	case FORMAT_FLOAT:
	     sscanf( yytext, "%f", &(st->fvalue));
	     break;
	}
	return st->index;
}

%}

%%

"$"			{ return -1; /* EOF */ }
"if"			{ return IF; }
"else"			{ return ELSE; }
"char"			{ yylval.index = CHAR; return CHAR; }
"short"			{ yylval.index = SHORT; return SHORT; }
"int"			{ yylval.index = INT; return INT; }
"long"			{ yylval.index = LONG; return LONG; }
{L}({L}|{D})*		{ yylval.index = (int) installIDENTIFIER(); return( IDENTIFIER); }
0[xX]{H}+{IS}?		{ yylval.index = (int) installCONSTANT( FORMAT_HEX); return( CONSTANT); }
0{D}+{IS}?		{ yylval.index = (int) installCONSTANT( FORMAT_OCTAL); return( CONSTANT); }
{D}+{IS}?		{ yylval.index = (int) installCONSTANT( FORMAT_DECIMAL); return( CONSTANT); }
{D}+{E}{FS}?		{ yylval.index = (int) installCONSTANT( FORMAT_FLOAT); return( CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ yylval.index = (int) installCONSTANT( FORMAT_FLOAT); return( CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ yylval.index = (int) installCONSTANT( FORMAT_FLOAT); return( CONSTANT); }
[ \n\t]			{ /* ignore white characters */ }
.			{ return( yytext[ 0]); /* return everything else */ }

%%

/*
 *	yy wrap function	always return NO
 */
yywrap()
{
	return( 1);
}

