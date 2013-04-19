#-----------------------------------------------------------------------------
#
# FILE:		Makefile
#
# DESC:		EECS 337 Assignment 3
#
# AUTHOR:		dls148
#
# DATE:		September 18, 2012
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

SRC	= gram.y scan.l main.c
OBJ	= gram.o scan.o main.o

universe :	$(OBJ)
	$(LINK) $(CFLAGS) $(OBJ) -o universe

scan.o	: y.tab.h

clean	:
	rm -f scan.c gram.c y.tab.h y.output *.o

totar	:
	tar cvf hw03_dls148.tar examples.y gram.y hw03_test.sh input1234.txt input1.txt main.c Makefile scan.l yystype.h

fromtar	:
	tar xvf hw03_dls148.tar 
