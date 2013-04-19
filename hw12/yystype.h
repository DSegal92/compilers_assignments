/*******************************************************************************
*
* FILE:		yystype.h 
*
* DESC:		EECS 337 Assignment 10
*
* AUTHOR:	dls148
*
* DATE:		November 13, 2012
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

/*
 *	define pic instructions
 */
#define I_LABEL		0
#define I_MOV		1
#define I_ADD		2
#define I_AND		3
#define I_IOR		4
#define I_SUB		5
#define I_XOR		6
#define I_COMF		7
#define I_DECF		8
#define I_DECFSZ	9
#define I_INCF		10
#define I_INCFSZ	11
#define I_RLF		12
#define I_RRF		13
#define	I_SWAPF		14
#define I_BCF		15
#define I_BSF		16
#define I_BTFSC		17
#define I_BTFSS		18
#define I_CALL		19
#define I_GOTO		20
#define I_TRIS		21
#define I_CLR		22
#define I_RETLW		23
#define I_CLRWDT	24
#define I_NOP		25
#define I_OPTION	26
#define I_RETFIE	27
#define I_RETURN	28
#define I_SLEEP		29
/*
 *	define a tuple structure
 *	supports: CONSTANT STRING_LITERAL IDENTIFIER types
 */
#define	TUPLE	struct tuple
TUPLE
{
	TUPLE		*next;
	int		token;
	unsigned char	value;
	int		address;
#define	MASK_VALUE	0x0001
#define	MASK_ADDRESS	0x0002
#define	MASK_LABEL	0x0004
#define	MASK_W_REG	0x0008
#define	MASK_F_REG	0x0010
#define	MASK_INSTR	0x0020
	int		mask;
	char		*buffer;
	int		length;
	int		level;
};

/*
 *	symbol table
 */
#define	SYMBOL_TABLE	struct symbol_table
SYMBOL_TABLE
{
	int	index;
	char	*string;
	int	length;
#define	TYPE_IDENTIFIER		1
#define	TYPE_CONSTANT		2
#define	TYPE_TEMPORARY		3
#define	TYPE_LABEL		4
	int	type;
#define	FORMAT_DECIMAL	1
#define	FORMAT_FLOAT	2
#define	FORMAT_OCTAL	3
#define	FORMAT_HEX	4
	int	format;
#define	FORMAT_CHAR	1 // identifiers
#define	FORMAT_SHORT	2
#define	FORMAT_INT	4
#define	FORMAT_LONG	8
	int	size;
	int	address;
	int	ivalue;
	float	fvalue;
	SYMBOL_TABLE	*next;
};
/*
 *	define a QUAD data structure that supports:
 *	1) X = Y op Z 	   binary op
 *	2) X = op Y   	   unary op
 *	3) X = Y      	   copy op
 */
#define	QUAD struct quad	
QUAD
{
	int	operator;
	int	dst_type;
	int	dst_index;
	int	op1_type;
	int	op1_index;
	int	op2_type;
	int	op2_index;
	QUAD	*next;
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
	int	errors;
	int	temp;
	int	memory;
	int	label;
/*
 *	symbol table
 */
	int	count;
	SYMBOL_TABLE *st;
#define	TOP_MEMORY	0x000c
#define	BOTTOM_MEMORY	0x004f
	int	address;
};

/*
 *	define for yyparser debugging
 */
#define	YYDEBUG	1
/*
 *	define yystype
 */
#define YYSTYPE union yycalc
YYSTYPE
{
	int	index;
	QUAD	*quad;
};

/*
 *	external functions from quad.c
 */
extern	void	new_error( int length);
extern	QUAD	*new_quad( int operator, int dst_type, int dst_index, int op1_type, int op1_index, int op2_type, int op2_index);
extern	void	free_quad( QUAD *quad);
extern	void	free_quad_list( QUAD *quad_list);
extern	QUAD	*end_quad_list( QUAD *quad_list);
extern	void	print_quad_operand( int type, int index);
extern	void	print_quad( QUAD *quad);
extern	void	print_quad_list( QUAD *quad_list);
extern	int	next_temp( void);
extern	QUAD	*new_quad1( int operator, QUAD *q1, QUAD *q2);
extern	QUAD	*new_quad2( int operator, QUAD *q1);
extern	QUAD	*new_quad3( int operator, int index);
/*
 *	new functions for IF ELSE and assignment productions
 */
extern	QUAD	*new_quad3A( int operator, int index, QUAD *q1);
extern	QUAD	*new_quad5( int operator, QUAD *q1, QUAD *q2);
extern	QUAD	*new_quad5E( int operator, QUAD *q1, QUAD *q2, QUAD *q3);
/*
 *	new functions for array and declaration productions
 */
extern	QUAD	*new_symbol( int type, int index);
extern	QUAD	*new_symbolARRAY( int type, int index, int constant);
extern	QUAD	*new_quad3ARRAY( int operator, int index, QUAD *q1, QUAD *q2);
extern	QUAD	*new_quad3E( int operator, int index, QUAD *q1);
/*
 *	external variables and functions from symbol.c
 */
extern	char	*new_buffer( char *text, int length);
extern	void	free_buffer( char *buffer, int length);
extern	SYMBOL_TABLE	*new_symbol_table( char *buffer, int length);
extern	void	free_symbol_table( SYMBOL_TABLE *symbol_table);
extern	void	free_symbol_table_list( SYMBOL_TABLE *symbol_table_list);
extern	SYMBOL_TABLE	*find_symbol_table_index( int index);
extern	SYMBOL_TABLE	*find_symbol_table_string( char *string);
/*
 *	external variables and functions from codegen.c
 */
extern	int	get_address( int size);
extern	TUPLE	*new_tuple( int token, unsigned char value, int address, int mask, char *buffer, int length);
extern	void	free_tuple( TUPLE *tuple);
extern	void	free_tuple_list( TUPLE *tuple);
extern	TUPLE	*end_tuple_list( TUPLE *tuple);
extern	TUPLE	*tuple_tail_to_head( TUPLE *head1, TUPLE *head2);
extern	void	print_tuple( TUPLE *tuple);
extern	void	print_tuple_list( TUPLE *tuple);
extern	void	code_generator_pic_prefix( void);
extern	void	code_generator_pic_postfix( void);
extern	void	code_generator_operand_postfix( TUPLE *tuple);
extern	void	code_generator_operand( TUPLE *tuple);
extern	void	code_generator_instr_postfix( TUPLE *tuple);
extern	void	code_generator_instr( TUPLE *tuple);
extern	void	code_generator_pic16f84( TUPLE *tuple_list);
extern	void	code_generator_instr_test( void);
/*
 *	external variables and functions from codegen2.c
 */
extern	void	code_generator_pic_address( void);
extern	TUPLE	*generate_quad_instruction( int instruction, int type, int index);
extern	TUPLE	*generate_quad_operand( int type, int index);
extern	TUPLE	*generate_quad_destination( int type, int index);
extern	TUPLE	*generate_quad( QUAD *quad);
extern	TUPLE	*generate_quad_2_tuple( QUAD *quad_list);
/*
 *	external variables and functions from lex.l
 */
extern	char *formats[];
extern	char *types[];
extern FILE	*yyin;
extern FILE	*yyout;
extern	char	*yytext;
extern	int	yyleng;
extern	int	yynerrs;
extern	YYSTYPE yylval;
extern	void	print_symbol_table( void);
extern	int	installIDENTIFIER( void);
extern	int	installCONSTANT( int format);
extern	int	yywrap( void);
/*
 *	external variables and functions from yacc.y
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
