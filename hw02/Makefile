#-----------------------------------------------------------------------------
#
# FILE: Makefile
#
# DESC: EECS 337 Assignment 2
#
# AUTHOR: dls148
#
# DATE: September 11, 2012
#
# EDIT HISTORY: Added header
#
#-----------------------------------------------------------------------------
.KEEP_STATE:

YFLAGS	= -dv
CFLAGS	= -O
LFLAGS	=

SRC	= gram.y scan.l main.c
OBJ	= gram.o scan.o main.o

$(BIN)/ansi_c :	$(OBJ)
	cc $(CFLAGS) $(OBJ) -o ansi_c

scan.o	: y.tab.h

clean	:
	rm -f y.tab.h y.output *.o scan.c gram.c
