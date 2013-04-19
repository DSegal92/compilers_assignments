#-----------------------------------------------------------------------------
#
# FILE:		Makefile
#
# DESC:		EECS 337 Assignment 11
#
# AUTHOR:	dls148
#
# DATE:		November 20, 2012
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

yacc.o	: codegen.c codegen2.c

clean	:
	rm -f yacc.c y.tab.h y.output *.o

totar	:
	tar cvf hw11_dls148.tar Makefile hw11_test.sh codegen.c codegen2.c math17.calc math18.calc math19.calc

fromtar	:
	tar xvf hw11_dls148.tar 
