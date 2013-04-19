/*******************************************************************************
*
* FILE:		yacc.y 
*
* DESC:		EECS 337 Assignment 6
* SYNOPSIS:	Calculator (page 292)
*
* AUTHOR:	dls148
*
* DATE:		October 9, 2012
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
double factor; /* keep track of digits past dot '.' */
int radix; /* keep track of decimal or octal format */

%}


%start lines

%token NUMBER

%left '|'
%left '^'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '~' /* supplies precedence for unary minus */

%%

letterValue
    : 'A' { $$ = 10; }
    | 'B' { $$ = 11; }
    | 'C' { $$ = 12; }
    | 'D' { $$ = 13; }
    | 'E' { $$ = 14; }
    | 'F' { $$ = 15; }
    | 'a' { $$ = 10; }
    | 'b' { $$ = 11; }
    | 'c' { $$ = 12; }
    | 'd' { $$ = 13; }
    | 'e' { $$ = 14; }
    | 'f' { $$ = 15; }
    ;
lines : lines expr '\n' { printf("%g\n", $2); }
      | lines '\n' 
    | /* empty */
    | error '\n' { yyerror(" reenter previous line: "); yyerrok; }
    ;
expr
    : expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = $1 / $3; }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = - $2; }
    | expr '|' expr { $$ = (int) $1 | (int) $3; }
    | expr '^' expr { $$ = (int) $1 ^ (int) $3; }
    | expr '&' expr { $$ = (int) $1 & (int) $3; }
    | expr '%' expr { $$ = (int) $1 % (int) $3; }
    | '~' expr { $$ = ~ (int) $2; }
    | number
    | exp
    | hex
    ;

exp
    : number 'e' number { $$ = pow(10, $3) * $1; }
    | number 'e' '-' number { $$ = $1 / pow(10, $4); }
    ;

hex
    : hexCompute letterValue { $$ = $2; }
    | hexCompute NUMBER { $$ = $2; }
    | hex NUMBER { $$ = $2 + $1 * radix; }
    ;

hexCompute
        : NUMBER 'x'
            {
                $$ = 0;
                if ($1 == 0) radix = 16;
                else {
                    yyerror("0 must preceede 'x'");
                    YYERROR;
                }
            }
        ;

number
        : NUMBER { $$ = $1; if ($1 == 0) radix = 8; else radix = 10; factor = 0; }
        | number NUMBER
            {
                if ($2 >= radix) {
                    yyerror ("number must be less than radix");
                    YYERROR;
                }
                if (factor > 0) {
                    factor *= 10;
                    $$ = $1 + $2 / factor;
                }
                else
                    $$ = $2 + $1 * radix;
            }
        | '.' NUMBER { factor = 10; radix = 10; $$ = $2 / factor; }
        | number '.' {
                factor = 1;
            }
        ;

%%
/*
 * start of post C programs
 */

void yyerror( char *s)
{
    printf( "%s\n", s);
}

#ifdef junk
/*
 * book sample code is non-functional
 */
yylex()
{
    int c;
    while(( c = getchar()) == ' ');
    if(( c == '.') || (isdigit(c)))
    {
         ungetc( c, stdin);
         scanf( "lf", &yylval);
         return NUMBER;
    }
}
#endif

/*
 * functional version of yylex()
 *
 * Input: yylval: Return:
 * space skip continue
 * tab skip continue
 * '$' - EOF
 * '\n' - '\n'
 * [0-9] value NUMBER
 * [.] - char
 * EOF - EOF
 */
yylex()
{
    int c;

    while(( c = getchar()) != 0)
    {
        if( c == ' ')
            continue;
        if( c == '\t')
            continue;
        if( c == '$')
            return( -1);
        if( c == '\n')
            return( '\n');
        if( isdigit( c))
        {
            yylval = c - '0'; /* convert single ascii digit ('0'-'9') to binary value (0-9) */
            return NUMBER;
        }
        return( c);
    }
    return( -1);
}


