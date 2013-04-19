#-----------------------------------------------------------------------------
#
# FILE:		Makefile
#
# DESC:		EECS 337 Assignment 8
#
# AUTHOR:		dls148
#
# DATE:		October 30, 2012
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

SRC	= yacc.y lex.l main.c
OBJ	= yacc.o lex.o main.o

calc :	$(OBJ)
	$(LINK) $(CFLAGS) $(OBJ) -o calc

lex.o	: y.tab.h quad.c

clean	:
	rm -f yacc.c y.tab.h y.output *.o

totar	:
	tar cvf hw08_dls148.tar Makefile hw08_test.sh lex.l yacc.y main.c math10.calc math11.calc yystype.h quad.c

fromtar	:
	tar xvf hw08_dls148.tar 
