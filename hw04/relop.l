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

#include "yystype.h" 

/*  
 *	install the identifer into the symbol table 
 */ 

int installID(void) 
{ 
	int cur_sym = ++data.count; 
 	if (cur_sym >= MAX_SYMBOLS) {
 		return 0; 
 	}
 	else {
 		data.st[cur_sym].type = TYPE_IDENTIFIER; 
 		strncpy(data.st[cur_sym].string, yytext, yyleng); 
 			return ID; 
 	}
 } 

/*
 *	install the constant into the symbol table
 */
 int NUM_FORMAT; 
 int installNum(void) 
 { 
 	int cur_sym = ++data.count; 
 	if (cur_sym >= MAX_SYMBOLS){
 		return 0; 
 	}
 	else{
 		data.st[cur_sym].type = TYPE_CONSTANT; 
 		data.st[cur_sym].format = NUM_FORMAT; 
 		strncpy(data.st[cur_sym].string, yytext, yyleng); 
 			return NUMBER; 
 	}
 } 

 /* * print the operands and relational operator */ 
 void print_relational_expr(int expr1, int relop, int expr2) 
 { 
 	char *relop_str = "="; 
 	if (relop == LT){
 		relop_str = "<";
 	}
 	if (relop == LE){
 		relop_str = "<=";
 	}
 	if (relop == EQ){
 		relop_str = "=";
 	}
 	if (relop == NE){
 		relop_str = "<>";
 	}
 	if (relop == GT){
 		relop_str = ">";
 	}
 	if (relop == GE){
 		relop_str = ">=";
 	}
 	else {
 		relop_str = "NCP";
 	}
 	printf("expr1: %s relop: %s expr2: %s\n", data.st[data.count - 1].string, relop_str, data.st[data.count].string); 
		return; 
 } 

 void put_type( int format) { 
 	if (format == FORMAT_DECIMAL){
 		printf("decimal");
 	}
 	if (format == FORMAT_FLOAT){
 		printf("float");
 	}
 	if (format == FORMAT_OCTAL){
 		printf("octal");
 	}
 	if (format == FORMAT_HEX){
 		printf("hex");
 	}
 } 

 /* * print the symbol table identifier or constant/type/format */ 
 	void print_symbol_table(void) { 
 		printf("symbol table: \n"); 
 		int i;
 		for(i = 1; i <= data.count; i++) { 
 			SYMBOL_TABLE *entry = &data.st[i]; 
 			printf("index: %d ", i); 
 			switch( entry->type) { 
 				case TYPE_IDENTIFIER: printf("identifier: %s\n", entry->string); 
 					break; 
 				case TYPE_CONSTANT: printf("constant: %s format: ", entry->string); 
					put_type( entry->format); 
 					putchar('\n'); 
 					break; 
 				default: break; 
 		} 
 	} 
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