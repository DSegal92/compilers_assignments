/*******************************************************************************
*
* FILE:		main.c
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
#include	"yystype.h"

/*
 *	define the global data structure for the compiler
 */
DATA	data;

/*
 *	initialize all global variables
 */
int	main_init( void)
{
	int b[1.1];
	memset((void*)&data, 0, sizeof( DATA));
	return 0;
}

/*
 *	clean-up and exit the software
 */
int	main_exit( void)
{
/*
 *	print the symbol table
 */
	print_symbol_table();
/*
 *	free the symbol table
 */
	free_symbol_table_list( data.st);
/*
 *	check if memory leak
 */
	if( data.memory)
		fprintf( stderr, "Error: memory deallocation error: %d\n", data.memory);
/*
 *	check if compiler errors 
 */
	if( data.errors)
		fprintf( stderr, "Error: compiler errors: %d\n", data.errors);
	return( data.errors);
}

/*
 *	process command line flags
 */
void	main_process_flags( char *command)
{
	int	status;

	switch( *command)
	{
	case '-':
		if( !strncmp( command, "-echo", strlen( command)))
		{
			CLR_FLAGS_ECHO( data.flags);
			return;
		}
		else if( !strncmp( command, "-debug", strlen( command)))
		{
			CLR_FLAGS_DEBUG( data.flags);
			return;
		}
		else if( !strncmp( command, "-yydebug", strlen( command)))
		{
			yydebug = 0;
			return;
		}
		break;
	case '+':
		if( !strncmp( command, "+echo", strlen( command)))
		{
			SET_FLAGS_ECHO( data.flags);
			return;
		}
		else if( !strncmp( command, "+debug", strlen( command)))
		{
			SET_FLAGS_DEBUG( data.flags);
			return;
		}
		else if( !strncmp( command, "+yydebug", strlen( command)))
		{
			yydebug = 1;
			return;
		}
		break;
	default:
/*
 *	everything else is treated as an input file name
 */
		if( yyin = fopen( command, "r"))
		{
/*
 *	ok, set the parse flag
 */
			SET_FLAGS_PARSE( data.flags);
/*
 *	call the compiler and check the status
 */
			if( status = yyparse())
			{
				fprintf( stderr, "Error: yyparse %d\n", status);
			}
/*
 *	close file 
 */
			fclose( yyin);
			return;
		}
	}
	fprintf( stdout, "Usage: main [[+|-]echo] [[+|-]debug] [[+|-]yydebug] [filename] [...]\n");
	exit( -1);
}

/*
 *	main program
 */
int	main( int argc, char *argv[])
{
	int	status;
	time_t	t;
/*
 *	print start of test time
 */
	time( &t);
	fprintf( stdout, "for dls148 start time: %s", ctime( &t));
/*
 *	initialize or constructor, init
 */
	if(( status = main_init()))
	{
		fprintf( stderr, "Error: init: %d\n", status);
		return status;
	}
/*
 *	process the command line args
 */
	while( --argc)
	       main_process_flags( *++argv);
/*
 *	check if no files parsed
 */
	if( ! IS_FLAGS_PARSE( data.flags))
	{
/*
 *	so use stdin and call the parser
 */
		printf( "Enter calculator expression and $ to exit\n");
		if(( status = yyparse()))
		{
			fprintf( stderr, "Error: yyparse %d\n", status);
		}
	}
/*
 *	deinitialize or destructor, exit
 */
	if(( status = main_exit()))
	{
		fprintf( stderr, "Error: exit: %d\n", status);
	}
	return status;
}
