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
	for( st = data.st; st; st = st->next)
	{
	     switch( st->type)
	     {
	     case TYPE_IDENTIFIER:
	     	     printf( "%s_ EQU 0x%x\n", st->string, st->address);
		     break;
	     case TYPE_CONSTANT:
		     break;
	     }
	}
/*
 *	generate the temporary addresses
 */
	printf( "; generate temporary addresses: \n");
	for( index = data.temp; 0 < index ; index--)
	     printf( "t%d_ EQU 0x%x\n", index, BOTTOM_MEMORY - index + 1);
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
	TUPLE *tuple = 0;
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
	     tuple = generate_quad_operand( quad->op2_type, quad->op2_index);
	     tuple->next = generate_quad_instruction( quad->operator, quad->op1_type, quad->op1_index);
	     tuple->next->next = generate_quad_destination( quad->dst_type, quad->dst_index);
	     break;
	case UMINUS:
	     tuple = generate_quad_operand( quad->op1_type, quad->op1_index);
	     tuple->next = new_tuple( I_SUB, 0x00, 0, MASK_VALUE, 0, 0);
	     tuple->next->next = generate_quad_destination( quad->dst_type, quad->dst_index);
	     break;
	case UPLUS:
	     tuple = generate_quad_operand( quad->op1_type, quad->op1_index);
	     tuple->next = generate_quad_destination( quad->dst_type, quad->dst_index);
	     break;
	case '~' :
	     tuple = generate_quad_instruction( quad->operator, quad->op1_type, quad->op1_index);
	     tuple->next = generate_quad_destination( quad->dst_type, quad->dst_index);
	     break;
	case '=':
	     tuple = generate_quad_operand( quad->op1_type, quad->op1_index);
	     tuple->next = generate_quad_destination( quad->dst_type, quad->dst_index);
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
	case '[':
	     break;
	case ']':
	     break;
	}
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
