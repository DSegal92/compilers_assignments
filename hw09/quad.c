/*******************************************************************************
*
* FILE:		quad.c
*
* DESC:		EECS 337 Assignment 8
*
* AUTHOR:	dls148
*
* DATE:		October 30, 2012
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
/*
 *	switch on the operand type
 */
	switch( type)
	{
	case TYPE_IDENTIFIER:
	case TYPE_CONSTANT:
	     printf( "%s", find_symbol_table_index(index)->string);
	     break;
	case TYPE_TEMPORARY:
	     printf( "t%d", index);
	     break;
	case TYPE_LABEL:
		printf("label%d", index);
		break;
	}
	return;
}

/*
 *	print a quad structure
 */
void	print_quad( QUAD *quad)
{
	printf("\t");
	switch( quad->operator)
	{
	case IF:
		printf("IFTRUE ");
		print_quad_operand(quad->dst_type, quad->dst_index);
		printf(" GOTO ");
		print_quad_operand(quad->op1_type, quad->op1_index);
		break;
	case LABEL:
		printf("\r");
		print_quad_operand(quad->dst_type, quad->dst_index);
		printf(": ");
		break;
	case GOTO:
		printf("GOTO ");
		print_quad_operand(quad->dst_type, quad->dst_index);
		break;
	case '|':
	case '^':
	case '&':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     printf( " %c ", quad->operator);
	     print_quad_operand( quad->op2_type, quad->op2_index);
	     break;
	case UMINUS:
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = - ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case UPLUS:
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = + ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case '~' :
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ~ ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case '=':
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
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

int next_label(void) {
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

	quad = new_quad( operator, TYPE_TEMPORARY, next_temp(), find_symbol_table_index(index)->type, index, 0, 0);
	return quad;
}

QUAD 	*new_quad3A(int operator, int index, QUAD *q1) {
	QUAD *quad1;
	quad1 = end_quad_list(q1);
	quad1->next = new_quad(operator, TYPE_IDENTIFIER, index, quad1->dst_type, quad1->dst_index, 0, 0);
	return q1;	
}


// operator = IF
// q1 = if (bla)
// q2 = then bla
QUAD 	*new_quad5(int operator, QUAD *q1, QUAD *q2) {
	int goto_label = next_label();
	QUAD *ifstatement, *thenstatement;
	ifstatement = end_quad_list(q1);
	ifstatement->next = new_quad(operator, ifstatement->dst_type, ifstatement->dst_index, TYPE_LABEL, goto_label, 0, 0);
	ifstatement->next->next = q2;
	thenstatement = end_quad_list(ifstatement);
	thenstatement->next = new_quad(LABEL, TYPE_LABEL, goto_label, 0, 0, 0, 0);	
	return q1;
}
// operator = IF
// q1 = if (bla)
// q2 = then bla
// q3 = else bla
QUAD	*new_quad5E(int operator, QUAD *q1, QUAD *q2, QUAD *q3) {
	int if_goto = next_label();
	int then_goto = next_label();
	QUAD *ifstatement, *thenstatement, *elsestatement;
	ifstatement = end_quad_list(q1);
	ifstatement->next = new_quad(operator, ifstatement->dst_type, ifstatement->dst_index, TYPE_LABEL, if_goto, 0, 0);
	ifstatement->next->next = q2;
	thenstatement = end_quad_list(ifstatement);
	thenstatement->next = new_quad(GOTO, TYPE_LABEL, then_goto, 0, 0, 0, 0);
	thenstatement->next->next = new_quad(LABEL, TYPE_LABEL, if_goto, 0, 0, 0, 0);
	thenstatement->next->next->next = q3;
	end_quad_list(q3)->next = new_quad(LABEL, TYPE_LABEL, then_goto, 0, 0, 0, 0);
	return q1;
}
