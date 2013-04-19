#-----------------------------------------------------------------------------
#
# FILE:		Makefile
#
# DESC:		EECS 337 Assignment 6
#
# AUTHOR:		dls148
#
# DATE:		October 9, 2012
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

SRC	= yacc.y calc.c
OBJ	= yacc.o calc.o

calc :	$(OBJ)
	$(LINK) $(CFLAGS) $(OBJ) -lm -o calc

clean	:
	rm -f yacc.c y.tab.h y.output *.o

totar	:
	tar cvf hw06_dls148.tar Makefile hw06_test.sh yacc.y calc.c math1.calc math2.calc math3.calc math4.calc math5.calc math6.calc math7.calc math8.calc math9.calc yystype.h

fromtar	:
	tar xvf hw06_dls148.tar 
