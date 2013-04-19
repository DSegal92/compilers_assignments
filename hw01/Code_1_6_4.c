/*******************************************************************************
*
* FILE:		Code_1_6_4.c
*
* DESC:		EECS 337 Homework Assignment 1
*
* AUTHOR:	dls148
*
* DATE:		August 28, 2012
*
* EDIT HISTORY:	
*	Added code from exercise 1.6.4
*
*******************************************************************************/
#include	<stdio.h>

#define a (x+1)
int x = 2;
void b() { x = a; printf("%d\n", x); }
void c() { int x = 1; printf("%d\n", a);}
int main() { b(); c(); }
