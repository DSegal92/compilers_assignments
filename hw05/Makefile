#-----------------------------------------------------------------------------
#
# FILE:		Makefile
#
# DESC:		EECS 337 Assignment 5
#
# AUTHOR:		dls148
#
# DATE:		October 2, 2012
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

hw05test :	$(OBJ)
	$(LINK) $(CFLAGS) $(OBJ) -o hw05test

scan.o	: y.tab.h

clean	:
	rm -f scan.c gram.c y.tab.h y.output *.o

totar	:
	tar cvf hw05_dls148.tar Makefile hw05_test.sh gramDFA.y gramNFA.y main.c scan.l test1.c test2.c test3.c yystype.h

fromtar	:
	tar xvf hw05_dls148.tar 

