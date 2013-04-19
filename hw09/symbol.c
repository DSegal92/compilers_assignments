/*******************************************************************************
*
* FILE:		symbol.c
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
/*
 *	allocate buffer memory routine
 */
char	*new_buffer( char *text, int length)
{
	char	*buffer = 0;

	if( 0 < length)
	{
		if( !( buffer = (char*)malloc( length)))
			new_error( length);
		else
		{
/*
 *	initialize the buffer to zero and copy in text
 */
			memset( (void *)buffer, 0, (size_t)length);
			strcpy( buffer, text);
			data.memory += length;
		}
	}
	return( buffer);
}

/*
 *	deallocate buffer memory routine
 */
void	free_buffer( char *buffer, int length)
{
	if( 0 < length)
	{
		free( buffer);
		data.memory -= length;
	}
	return;
}

/*
 *	allocate a symbol table data structure
 */
SYMBOL_TABLE	*new_symbol_table( char *buffer, int length)
{
	SYMBOL_TABLE *symbol_table;

	if( !(symbol_table = ( SYMBOL_TABLE*)malloc( sizeof( SYMBOL_TABLE))))
		new_error( sizeof( SYMBOL_TABLE));
	else
	{
		memset( (void *)symbol_table, 0, (size_t)sizeof( SYMBOL_TABLE));
		if( length)
		{
			symbol_table->string = new_buffer( buffer, length);
			symbol_table->length = length;
			symbol_table->index = data.count++;
		}
		data.memory += sizeof( SYMBOL_TABLE);
	}
	return( symbol_table);
}

/*
 *	deallocate a symbol_table data structure
 */
void	free_symbol_table( SYMBOL_TABLE *symbol_table)
{
	if( symbol_table)
	{
		if( symbol_table->length)
			free_buffer( symbol_table->string, symbol_table->length);
		free( symbol_table);
		data.memory -= sizeof( SYMBOL_TABLE);
	}
	data.temp = 0;
	return;
}

/*
 *	deallocate a symbol_table linked list
 */
void	free_symbol_table_list( SYMBOL_TABLE *symbol_table_list)
{
	SYMBOL_TABLE	*symbol_table_next;
/*
 *	deallocate the symbol_table linked list structure
 */
	while( symbol_table_list)
	{
		symbol_table_next = symbol_table_list->next;
		free_symbol_table( symbol_table_list);
		symbol_table_list = symbol_table_next;
	}
	return;
}

/*
 *	find is symbol table index in the symbol table
 */
SYMBOL_TABLE	*find_symbol_table_index( int index)
{
	SYMBOL_TABLE *st;
/*
 *	search for the previous index
 */
	for( st = data.st; st; st = st->next)
	     if( st->index == index)
	     	 break;
	return st;
}

