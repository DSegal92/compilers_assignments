/*******************************************************************************
*
* FILE:		quad.c
*
* DESC:		EECS 337 Assignment 9
*
* AUTHOR:	dls148
*
* DATE:		November 6, 2012
*
* EDIT HISTORY:	
*
*******************************************************************************/

/*******************************************************************************
 *
 *	dynamic memory routines
 *
 ******************************************************************************/
/*
 *	memory allocation error (FATAL no return!)
 */
void	new_error( int length)
{
	fprintf( stderr, "Fatal error: memory allocation failure: %d\n", length);
	exit( -1);
}

/*
 *	allocate a quad data structure
 */
QUAD	*new_quad( int operator, int dst_type, int dst_index, int op1_type, int op1_index, int op2_type, int op2_index)
{
	QUAD *quad;

	if( !(quad = ( QUAD*)malloc( sizeof( QUAD))))
		new_error( sizeof( QUAD));
	else
	{
		memset( (void *)quad, 0, (size_t)sizeof( QUAD));
		quad->operator = operator;
		quad->dst_type = dst_type;
		quad->dst_index = dst_index;
		quad->op1_type = op1_type;
		quad->op1_index = op1_index;
		quad->op2_type = op2_type;
		quad->op2_index = op2_index;
		data.memory += sizeof( QUAD);
	}
	return( quad);
}

/*
 *	deallocate a quad data structure

 */
void	free_quad( QUAD *quad)
{
	if( quad)
	{
		free( quad);
		data.memory -= sizeof( QUAD);
	}
	return;
}

/*
 *	deallocate a quad linked list
 */
void	free_quad_list( QUAD *quad_list)
{
	QUAD	*quad_next;
/*
 *	deallocate the quad linked list structure
 */
	while( quad_list)
	{
		quad_next = quad_list->next;
		free_quad( quad_list);
		quad_list = quad_next;
	}
/*
 *	set the temporary variable back to zero
 */
	data.temp = 0;
	return;
}

/*
 *	find the last quad structure in linked list
 */
QUAD	*end_quad_list( QUAD *quad_list)
{
	if( quad_list)
		while( quad_list->next)
			quad_list = quad_list->next;
	return quad_list;
}

/*
 *	print a quad operand structure
 */
void	print_quad_operand( int type, int index)
{
	SYMBOL_TABLE *st;
/*
 *	switch on the operand type
 */
	switch( type)
	{
	case TYPE_IDENTIFIER:
	case TYPE_CONSTANT:
/*
 *	find this index in the symbol table
 */
	     st = find_symbol_table_index( index);
	     printf( "%s", st->string);
	     break;
	case TYPE_TEMPORARY:
	     printf( "t%d", index);
	     break;
	case TYPE_LABEL:
	     printf( "label%d", index);
	     break;
	}
	return;
}

/*
 *	print a quad structure
 */
void	print_quad( QUAD *quad)
{
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
	     printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     printf( " %c ", quad->operator);
	     print_quad_operand( quad->op2_type, quad->op2_index);
	     break;
	case UMINUS:
	     printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = - ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case UPLUS:
	     printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = + ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case '~' :
	     printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ~ ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case '=':
	     printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case IF:
	     printf( "\t");
	     printf( "IFTRUE ");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " GOTO ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case LABEL:
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( ": ");
	     break;
	case GOTO:
	     printf( "\t");
	     printf( "GOTO ");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     break;
	case '[': 
	    printf( "\t"); 
	    print_quad_operand( quad->dst_type, quad->dst_index); 
	    printf( " [ "); 
	    print_quad_operand( quad->op1_type, quad->op1_index); 
	    printf( " ] = "); 
	    print_quad_operand( quad->op2_type, quad->op2_index); 
	    break; 
	case ']': 
	     printf( "\t"); 
	     print_quad_operand( quad->dst_type, quad->dst_index); 
	     printf( " = "); 
	     print_quad_operand( quad->op1_type, quad->op1_index); 
	     printf( " [ "); 
	     print_quad_operand( quad->op2_type, quad->op2_index); 
	     printf( " ] "); 
	     break;

	}
	printf( "\n");
	//	printf( "\nnext: %08.8x\n", (int)quad->next);
	return;
}

/*
 *	print a quad linked list
 */
void	print_quad_list( QUAD *quad_list)
{
	QUAD	*quad;
/*
 *	print the quad linked list structure
 */
	for( quad = quad_list; quad; quad = quad->next)
	{
		print_quad( quad);
	}
	return;
}

/*
 *	allocate the next temporary location
 */
int	next_temp( void)
{
	return ++data.temp;
}

/*
 *	allocate the next label location
 */
int	next_label( void)
{
	return ++data.label;
}

/*
 *	allocate a quad1 function
		$$.quad = new_quad1( '+', $1.quad, $3.quad);
 */
QUAD	*new_quad1( int operator, QUAD *q1, QUAD *q2)
{
	QUAD	*quad1;
	QUAD	*quad2;

	quad1 = end_quad_list( q1);
	quad1->next = q2;
	quad2 = end_quad_list( q2);
	quad2->next = new_quad( operator, TYPE_TEMPORARY, next_temp(), quad1->dst_type, quad1->dst_index, quad2->dst_type, quad2->dst_index);
	return q1;
}


QUAD *new_symbol( int type, int index) { 
	QUAD *quad = 0; 
	SYMBOL_TABLE *st; 
	st = find_symbol_table_index( index); 

	switch(type) { 
		case CHAR: 
			st->format = FORMAT_CHAR; 
			break; 
		case SHORT: 
			st->format = FORMAT_SHORT; 
			break; 
		case INT: 
			st->format = FORMAT_INT; 
			break; 
		case LONG: 
			st->format = FORMAT_LONG; 
			break; 
	} 
	st->size = 1; 
	return quad; 
} 

QUAD *new_symbolARRAY( int type, int index, int constant) { 
	QUAD *quad = 0; 
	SYMBOL_TABLE *st; 
	SYMBOL_TABLE *stC; 
	long lvalue; 
	st = find_symbol_table_index( index); 
	switch(type) { 
		case CHAR: 
			st->format = FORMAT_CHAR; 
			break; 
		case SHORT: 
			st->format = FORMAT_SHORT; 
			break; 
		case INT: 
			st->format = FORMAT_INT; 
			break; 
		case LONG: 
			st->format = FORMAT_LONG; 
			break; 
	} 
	stC = find_symbol_table_index( constant); 
 
	switch( stC->format) { 
		case FORMAT_HEX: 
			sscanf( stC->string, "%lx", &lvalue); 
			break; 
		case FORMAT_OCTAL: 
			sscanf( stC->string, "%lo", &lvalue); 
			break; 
		case FORMAT_DECIMAL: 
			sscanf( stC->string, "%ld", &lvalue); 
			break; 
		case FORMAT_FLOAT: 
			data.errors++; 
			fprintf( stderr, "error: size of array .%s. has non-integer type\n", st->string); 
			lvalue = 0; 
			break; 
	} 
	st->size = lvalue; 
	return quad; 
} 
/*
 *	allocate a quad2 function
		$$.quad = new_quad2( '~', $1.quad);
 */
QUAD	*new_quad2( int operator, QUAD *q1)
{
	QUAD	*quad1;

	quad1 = end_quad_list( q1);
	quad1->next = new_quad( operator, TYPE_TEMPORARY, next_temp(), quad1->dst_type, quad1->dst_index, 0, 0);
	return q1;
}
/*
 *	allocate a quad3 function
		$$.quad = new_quad3( '=', $1.index);
 */
QUAD	*new_quad3( int operator, int index)
{
	QUAD	*quad;
	SYMBOL_TABLE	*st;
/*
 *	find this index in the symbol table
 */
	st = find_symbol_table_index( index);
	quad = new_quad( operator, TYPE_TEMPORARY, next_temp(), st->type, index, 0, 0);
	return quad;
}

/*
 *	allocate a quad3A (assign) function
		$$.quad = new_quad3A( '=', $1.index, $3.quad);
 */
QUAD	*new_quad3A( int operator, int index, QUAD *q1)
{
	QUAD	*quad1;
	SYMBOL_TABLE	*st;
/*
 *	find this index in the symbol table
 */
	st = find_symbol_table_index( index);
	quad1 = end_quad_list( q1);
	quad1->next = new_quad( operator, st->type, index, quad1->dst_type, quad1->dst_index, 0, 0);
	return q1;
}

/*
 *	allocate a quad5 function
		$$.quad = new_quad5( IF, $3,quad, $5.quad);
 */
QUAD	*new_quad5( int operator, QUAD *q1, QUAD *q2)
{
	QUAD	*quad;
	int	label;

	quad = end_quad_list( q1);
	label = next_label();
	quad->next = new_quad( operator, quad->dst_type, quad->dst_index, TYPE_LABEL, label, 0, 0);
	quad->next->next = q2;
	quad = end_quad_list( q2);
	quad->next = new_quad( LABEL, TYPE_LABEL, label, 0, 0, 0, 0);
	return q1;
}

/* 
 * 
allocate a quad3ARRAY (assign) function 
$$.quad = new_quad3ARRAY( '=', $1.index, $3.quad, $6.quad); 
 */ 
QUAD *new_quad3ARRAY( int operator, int index, QUAD *q1, QUAD *q2) { 
	QUAD *quad1;
	QUAD *quad2;
	QUAD *array_index_quad;

	SYMBOL_TABLE *array;
	SYMBOL_TABLE *arrayType;

	array = find_symbol_table_index(index);
	quad1 = end_quad_list(q1);
	quad2 = end_quad_list(q2);
	char buffer[16];

	// For the input:
	// int a; 
	// int b[10];
	// b[ a + 1] = a; 
	// Our output should be:
	//	t1 = a 
	//	t2 = 1 
	//	t3 = t1 + t2 	// t3 is end_quad_list(q1)
	// 	t5 = t3 * 4 	// dat four...
	//	t4 = a		// given by q2 (do we want end_quad_list?) 
	//	b [ t5 ] = t4 
	// So, we make a quad with the '[' operand
	// 	dst is b
	//	op1 is t5
	// 	op2 is t4
	
	sprintf(buffer, "%d", array->format);
	arrayType = find_symbol_table_string(buffer);
	if (!arrayType) {
		arrayType = new_symbol_table(buffer, 2);
		arrayType->type = TYPE_CONSTANT;
		arrayType->format = FORMAT_DECIMAL;
		arrayType->next = data.st;
		data.st = arrayType;
	}
	
	array_index_quad = new_quad('*', TYPE_TEMPORARY, next_temp(), quad1->dst_type, quad1->dst_index, arrayType->type, arrayType->index);

	quad1->next = array_index_quad;
	array_index_quad->next = q2;
	quad2->next = new_quad('[', array->type, index, array_index_quad->dst_type, array_index_quad->dst_index, quad2->dst_type, quad2->dst_index);
	return q1; 
}


QUAD *new_quad3E( int operator, int index, QUAD *q1) { 
	QUAD *quad1; 
	SYMBOL_TABLE *st; 
	SYMBOL_TABLE *stC;  
	char buffer[ 16]; 
	st = find_symbol_table_index( index); 
	quad1 = end_quad_list( q1); 
	if( st->format == FORMAT_CHAR) {
		quad1->next = new_quad( operator, TYPE_TEMPORARY, next_temp(), st->type, index, quad1->dst_type, quad1->dst_index); 
	} else { 
		sprintf( buffer, "%d", st->format); 
		stC = find_symbol_table_string( buffer); 
		if( ! stC) { 
			stC = new_symbol_table( buffer, 2); 
			stC->type = TYPE_CONSTANT; 
			stC->format = FORMAT_DECIMAL; 
			stC->next = data.st; 
			data.st = stC; 
		} 
		quad1->next = new_quad( '*', TYPE_TEMPORARY, next_temp(), quad1->dst_type, quad1->dst_index, stC->type, stC->index); 
		quad1->next->next = new_quad( operator, TYPE_TEMPORARY, next_temp(), st->type, index, quad1->next->dst_type, quad1->next->dst_index); 
	} 
	return q1; 
} 

/*
 *	allocate a quad5 function
		$$.quad = new_quad5E( IF, $3,quad, $5.quad, $7.quad);
 */
QUAD	*new_quad5E( int operator, QUAD *q1, QUAD *q2, QUAD *q3)
{
	QUAD	*quad;
	int	label1;
	int	label2;

	label1 = next_label();
	label2 = next_label();
	quad = end_quad_list( q1);
	quad->next = new_quad( operator, quad->dst_type, quad->dst_index, TYPE_LABEL, label1, 0, 0);
	quad->next->next = q2;
	quad = end_quad_list( q2);
	quad->next = new_quad( GOTO, TYPE_LABEL, label2, 0, 0, 0, 0);
	quad->next->next = new_quad( LABEL, TYPE_LABEL, label1, 0, 0, 0, 0);
	quad->next->next->next = q3;
	quad = end_quad_list( q3);
	quad->next = new_quad( LABEL, TYPE_LABEL, label2, 0, 0, 0, 0);
	return q1;
}

