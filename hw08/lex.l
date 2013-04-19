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
	int	index;

	printf( "symbol table: \n");
	for( index = 0; index < data.count; index++)
	{
	     switch( data.st[ index].type) {
	     case TYPE_IDENTIFIER:
	     	     printf( "index: %d identifier: %s\n", index, data.st[ index].string);
		     break;
	     case TYPE_CONSTANT:
	     	     printf( "index: %d constant: %s format: %s\n", index, data.st[ index].string, formats[ data.st[ index].format]);
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
	int index;
/*
 *	search for the previous string
 */
	for( index = 0; index < data.count; index++)
	     if( ! strcmp( data.st[ index].string, yytext))
	     	 return index;
/*
 *	create a new entry
 */
	strcpy( data.st[ data.count].string, yytext);
	data.st[ data.count].type = TYPE_IDENTIFIER;
	return data.count++;
}

/*
 *	install the constant into the symbol table
 */
int installCONSTANT( int format)
{
	int index;
/*
 *	search for the previous string
 */
	for( index = 0; index < data.count; index++)
	     if( ! strcmp( data.st[ index].string, yytext))
	     	 return index;
/*
 *	create a new entry
 */
	strcpy( data.st[ data.count].string, yytext);
	data.st[ data.count].type = TYPE_CONSTANT;
	data.st[ data.count].format = format;
	return data.count++;
}

%}

%%

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

