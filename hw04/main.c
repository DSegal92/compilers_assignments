/*******************************************************************************
*
* FILE:		main.c
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
#include	"yystype.h"

/*
 *	define the global data structure for the compiler
 */
DATA	data;

/*
 *	initialize all global variables
 */
int	ifrelop_init( void)
{
	memset((void*)&data, 0, sizeof( DATA));
	return 0;
}

/*
 *	clean-up and exit the software
 */
int	ifrelop_exit( void)
{
/*
 *	print the symbol table
 */
	print_symbol_table();
	return 0;
}

/*
 *	process command line flags
 */
void	ifrelop_process_flags( char *command)
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
	fprintf( stdout, "Usage: ifrelop [[+|-]echo] [[+|-]debug] [[+|-]yydebug] [filename] [...]\n");
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
	if(( status = ifrelop_init()))
	{
		fprintf( stderr, "Error: init: %d\n", status);
		return status;
	}
/*
 *	process the command line args
 */
	while( --argc)
	       ifrelop_process_flags( *++argv);
/*
 *	check if no files parsed
 */
	if( ! IS_FLAGS_PARSE( data.flags))
	{
/*
 *	so use stdin and call the parser
 */
		if(( status = yyparse()))
		{
			fprintf( stderr, "Error: yyparse %d\n", status);
		}
	}
/*
 *	deinitialize or destructor, exit
 */
	if(( status = ifrelop_exit()))
	{
		fprintf( stderr, "Error: exit: %d\n", status);
	}
	return status;
}
