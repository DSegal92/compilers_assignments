#-----------------------------------------------------------------------------
#
# FILE:		Makefile
#
# DESC:		EECS 337 Assignment 4
#
# AUTHOR:		dls148
#
# DATE:		September 25, 2012
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

SRC	= ifthen.y relop.l main.c
OBJ	= ifthen.o relop.o main.o

ifrelop :	$(OBJ)
	$(LINK) $(CFLAGS) $(OBJ) -o ifrelop

relop.o	: y.tab.h

clean	:
	rm -f relop.c ifthen.c y.tab.h y.output *.o

totar	:
	tar cvf hw04_dls148.tar Makefile hw04_test.sh ifthen.y main.c relop.l test1.c test2.c test3.c test4.c test5.c yystype.h

fromtar	:
	tar xvf hw04_dls148.tar 
