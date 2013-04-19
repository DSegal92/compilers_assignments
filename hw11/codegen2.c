/*******************************************************************************
*
* FILE:		codegen2.c
*
* DESC:		EECS 337 Assignment 11
*
* AUTHOR:	dls148
*
* DATE:		November 20, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/

/*
 *	generate the symbols and temporary address
 */
void	code_generator_pic_address( void)
{
	SYMBOL_TABLE *st;
	int	     index;

	printf( "; generate symbol table: \n");

	// for each entry in the symbol table
	// 	print: <name>_ EQU <memory address>
	// 		where the memory address starts at 0xC and goes up.
	for (st = data.st; st; st = st->next) {
		// We only want to deal with identifiers, constants get dealt with later (I think...)
		if (st->type == TYPE_IDENTIFIER) {
			printf("%s_ EQU 0x%X\n", st->string, st->address);
		}
	}

/*
 *	generate the temporary addresses
 */
	printf( "; generate temporary addresses: \n");

	// for each quad, we take it's t<value> and start from the bottom and move up

	for (index = 1; index <= data.temp; index++) {
		printf("t%d_ EQU 0x%X\n", index, BOTTOM_MEMORY - (index - 1));
	}

	return;
}

/*
 *	generate the quad operand
 */
TUPLE	*generate_quad_instruction( int instruction, int type, int index)
{
	TUPLE	*tuple;
	SYMBOL_TABLE *st;
	char	buffer[ 16];
	int	value;
/*
 *	switch on the operand type
 */
	switch( type)
	{
	case TYPE_IDENTIFIER:
/*
 *	find this index in the symbol table
 */
	     st = find_symbol_table_index( index);
	     sprintf( buffer, "%s_", st->string);
	     value = strlen( buffer) + 1;
	     switch( instruction)
	     {
	     case '|':
	     	  tuple = new_tuple( I_IOR, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '^':
	     	  tuple = new_tuple( I_XOR, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '&':
	     	  tuple = new_tuple( I_AND, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '+':
	     	  tuple = new_tuple( I_ADD, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '-':
	     	  tuple = new_tuple( I_SUB, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '*':
	     	  tuple = new_tuple( I_NOP, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '/':
	     	  tuple = new_tuple( I_NOP, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '%':
	     	  tuple = new_tuple( I_NOP, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '~':
	     	  tuple = new_tuple( I_COMF, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '[':
	     	  tuple = new_tuple( I_ADD, 0, 0, MASK_LABEL, buffer, value);
	     	  break;
	     }
	     break;
	case TYPE_TEMPORARY:
	     sprintf( buffer, "t%d_", index);
	     value = strlen( buffer) + 1;
	     switch( instruction)
	     {
	     case '|':
	     	  tuple = new_tuple( I_IOR, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '^':
	     	  tuple = new_tuple( I_XOR, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '&':
	     	  tuple = new_tuple( I_AND, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '+':
	     	  tuple = new_tuple( I_ADD, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '-':
	     	  tuple = new_tuple( I_SUB, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '*':
	     	  tuple = new_tuple( I_NOP, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '/':
	     	  tuple = new_tuple( I_NOP, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '%':
	     	  tuple = new_tuple( I_NOP, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '~':
	     	  tuple = new_tuple( I_COMF, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     	  break;
	     case '[':
	     	  tuple = new_tuple( I_ADD, 0, 0, MASK_LABEL, buffer, value);
	     	  break;
	     }
	     break;
	case TYPE_CONSTANT:
/*
 *	find this index in the symbol table
 */
	     st = find_symbol_table_index( index);
	     switch( st->format)
	     {
	     case FORMAT_HEX:
	     case FORMAT_OCTAL:
	     case FORMAT_DECIMAL:
	     	  value = st->ivalue;
	     	  break;
	     case FORMAT_FLOAT:
	     	  data.errors++;
	     	  fprintf( stderr, "error: PIC does not support floating point values: %s\n", st->string);
	     	  value = 0;
	     	  break;
	     }
	     switch( instruction)
	     {
	     case '|':
	     	  tuple = new_tuple( I_IOR, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '^':
	     	  tuple = new_tuple( I_XOR, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '&':
	     	  tuple = new_tuple( I_AND, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '+':
	     	  tuple = new_tuple( I_ADD, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '-':
	     	  tuple = new_tuple( I_SUB, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '*':
	     	  tuple = new_tuple( I_NOP, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '/':
	     	  tuple = new_tuple( I_NOP, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '%':
	     	  tuple = new_tuple( I_NOP, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '~':
	     	  tuple = new_tuple( I_COMF, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     case '[':
	     	  tuple = new_tuple( I_ADD, value, 0, MASK_VALUE, 0, 0);
	     	  break;
	     }
	     break;
	case TYPE_LABEL:
	     sprintf( buffer, "label%d", index);
	     value = strlen( buffer) + 1;
	     switch( instruction)
	     {
	     case GOTO:
	     	  tuple = new_tuple( I_GOTO, 0, 0, MASK_LABEL, buffer, value);
	     	  break;
	     }
	     break;
	}
	return tuple;
}

/*
 *	generate the quad operand
 */
TUPLE	*generate_quad_operand( int type, int index)
{
	TUPLE	*tuple;
	SYMBOL_TABLE *st;
	char	buffer[ 16];
	int	value;
/*
 *	switch on the operand type
 */
	switch( type)
	{
	case TYPE_IDENTIFIER:
/*
 *	find this index in the symbol table
 */
	     st = find_symbol_table_index( index);
	     sprintf( buffer, "%s_", st->string);
	     value = strlen( buffer) + 1;
	     tuple = new_tuple( I_MOV, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     break;
	case TYPE_TEMPORARY:
	     sprintf( buffer, "t%d_", index);
	     value = strlen( buffer) + 1;
	     tuple = new_tuple( I_MOV, 0, 0, MASK_LABEL | MASK_W_REG, buffer, value);
	     break;
	case TYPE_LABEL:
	     sprintf( buffer, "label%d", index);
	     value = strlen( buffer) + 1;
	     tuple = new_tuple( I_LABEL, 0, 0, MASK_LABEL, buffer, value);
	     break;
	case TYPE_CONSTANT:
/*
 *	find this index in the symbol table
 */
	     st = find_symbol_table_index( index);
	     switch( st->format)
	     {
	     case FORMAT_HEX:
	     case FORMAT_OCTAL:
	     case FORMAT_DECIMAL:
	     	  value = st->ivalue;
	     	  break;
	     case FORMAT_FLOAT:
	     	  data.errors++;
	     	  fprintf( stderr, "error: PIC does not support floating point values: %s\n", st->string);
	     	  value = 0;
	     	  break;
	     }
	     tuple = new_tuple( I_MOV, value, 0, MASK_VALUE, 0, 0);
	     break;
	}
	return tuple;
}

/*
 *	generate the quad destination
 */
TUPLE	*generate_quad_destination( int type, int index)
{
	TUPLE	*tuple;
	SYMBOL_TABLE *st;
	char	buffer[ 16];
	int	value;
/*
 *	switch on the operand type
 */
	switch( type)
	{
	case TYPE_IDENTIFIER:
/*
 *	find this index in the symbol table
 */
	     st = find_symbol_table_index( index);
	     sprintf( buffer, "%s_", st->string);
	     value = strlen( buffer) + 1;
	     tuple = new_tuple( I_MOV, 0, 0, MASK_LABEL, buffer, value);
	     break;
	case TYPE_TEMPORARY:
	     sprintf( buffer, "t%d_", index);
	     value = strlen( buffer) + 1;
	     tuple = new_tuple( I_MOV, 0, 0, MASK_LABEL, buffer, value);
	     break;
	case TYPE_LABEL:
	     sprintf( buffer, "label%d", index);
	     value = strlen( buffer) + 1;
	     tuple = new_tuple( I_LABEL, 0, 0, MASK_LABEL, buffer, value);
	     break;
	case TYPE_CONSTANT:
	     tuple = 0;
	     break;
	}
	return tuple;
}

/*
 *	generate the tuple from quad 
 */
TUPLE	*generate_quad( QUAD *quad)
{
	printf("*** Quad:\n\t");
	print_quad(quad);
	


	TUPLE *tuple = 0;
	SYMBOL_TABLE *st;
	char    buffer[ 16];
	int     value;

	switch( quad->operator)
	{
	case '|':
	case '^':
	case '&':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
		// Move <op1> to w
		tuple = generate_quad_operand(quad->op1_type, quad->op1_index);
		// Add w to <op2>
		tuple->next = generate_quad_instruction(quad->operator, quad->op2_type, quad->op2_index);
		// Move w into <dst>
		tuple->next->next = generate_quad_destination(quad->dst_type, quad->dst_index);
	     break;
	case UMINUS:
		// To negate a number, take the one's complement and add one... Right?

		// Move <op1> to w
		tuple = generate_quad_operand(quad->op1_type, quad->op1_index);
		// Take the one's complement of w
		tuple->next = generate_quad_instruction('~', quad->op1_type, quad->op1_index);
		// Move w into <op1>
		tuple->next->next = generate_quad_destination(quad->op1_type, quad->op1_index);
		// w = <op1> + 1
		sprintf( buffer, "t%d_", quad->op1_index);
		value = strlen( buffer) + 1;
		tuple->next->next->next = new_tuple(I_INCF, 0, 0,  MASK_LABEL | MASK_W_REG , buffer, value);
		// <dst> = <op1>
		tuple->next->next->next->next = generate_quad_destination(quad->dst_type, quad->dst_index);
	     break;
	case UPLUS:
		// And next we have the most useless instruction ever.
		// No seriously, it's useless
		// <dst> = + <op1> can be rewritten as...
		// <dst> = <op1> AND <op1>
		// And since we all love recursion!
		tuple = generate_quad(new_quad('&', quad->dst_type, quad->dst_index, quad->op1_type, quad->op1_index, quad->op1_type, quad->op1_index));
	     break;
	case '~' :
		// Negate <op1>
		tuple = generate_quad_instruction('~', quad->op1_type, quad->op1_index);
		// Move <op1> into <dst>
		tuple->next = generate_quad_destination(quad->dst_type, quad->dst_index);
	     break;
	case '=':
	     tuple = generate_quad_operand( quad->op1_type, quad->op1_index);
	     tuple->next = generate_quad_destination( quad->dst_type, quad->dst_index);
	     break;
	case '[':




	     break;
	case ']':
// this is crap = array[index]
/* the quad 

t5 = b [ t4 ]

 code I want to generate: 
movf t4_, W
addlw b_
movwf FSR
movf INDR, W
movwf t5_
movf t1_,
*/

		//tuple = generate_quad_destination(quad->op2_type, quad->op2_index);
		//tuple->next = new_tuple(I_ADDLW, 0, 0, MASK_LABEL, 0, 0);
	     break;
	case IF: 
	     tuple = generate_quad_operand( quad->dst_type, quad->dst_index); 
	     tuple->next = new_tuple( I_BTFSC, 0x02, 0x03, MASK_VALUE | MASK_ADDRESS, 0, 0); // BTFSC STATUS, Z  
	     tuple->next->next = generate_quad_instruction( GOTO, quad->op1_type, quad->op1_index); 
	     break; 
	case LABEL:  
	     tuple = generate_quad_operand( quad->dst_type, quad->dst_index); 
	     break; 
	case GOTO:
	     tuple = generate_quad_instruction( GOTO, quad->dst_type, quad->dst_index); 
	     break; 
	}
	printf("**** PIC Assembly:\n");
	TUPLE *loop = tuple;
	while (loop) {
		code_generator_instr(loop);
		loop = loop->next;
	}
	printf("**** End Quad->Tuple (And by Tuple we mean assembly)...\n");
	return tuple;
}

/*
 *	generate the tuple from quad list
 */
TUPLE	*generate_quad_2_tuple( QUAD *quad_list)
{
	TUPLE *tuple;
	TUPLE *tuple_tail;
	QUAD	*quad;
/*
 *	create nop on head of list
 */
	tuple = new_tuple( I_NOP, 0, 0, MASK_INSTR, 0, 0);
	tuple_tail = tuple;
/*
 *	generate the quad linked list structure
 */
	for( quad = quad_list; quad; quad = quad->next)
	{
		tuple_tail->next = generate_quad( quad);
		tuple_tail = end_tuple_list( tuple_tail);
	}
	return tuple;
}