#-----------------------------------------------------------------------------
#
# FILE:		Makefile
#
# DESC:		EECS 337 Assignment 7
#
# AUTHOR:		dls148
#
# DATE:		October 16, 2012
#
# EDIT HISTORY:	
#
#-----------------------------------------------------------------------------
.KEEP_STATE:
SHELL=/bin/bash

#
#	define version of c compiler, linker and lex
#
CC=	gcc
LINK=	gcc
LEX=	lex
#
#	define yacc lex and compiler flags
#
YFLAGS	= -dv
LFLAGS	=
CFLAGS	= -g

#
#	to make all
#
all:		calc 

SRC	= yacc.y lex.l calc.c
OBJ	= yacc.o lex.o calc.o

calc :	$(OBJ)
	$(LINK) $(CFLAGS) $(OBJ) -lm -o calc

lex.o	: y.tab.h

clean	:
	rm -f yacc.c y.tab.h y.output *.o

totar	:
	tar cvf hw07_dls148.tar Makefile hw07_test.sh lex.l yacc.y calc.c yystype.h

fromtar	:
	tar xvf hw07_dls148.tar 
