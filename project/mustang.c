/*******************************************************************************
*
* FILE:		tbird.c
*
* DESC:		EECS 337 Project Extra Credit
*
* AUTHOR:	dls148
*
* DATE:		December 6, 2012
*
* EDIT HISTORY:	
*
*	tbird tail lights are defined using 3 bits per side
*	0000 0000 all off
*	0111 1110 hazard on
*	0000 1000 right on 1
*	0000 1100 right on 2
*	0000 1110 right on 3
*	0001 0000 left on 1
*	0011 0000 left on 2
*	0111 0000 left on 3
*******************************************************************************/
char	lights = 0;
char	index;
char	count;

delay()
{
	index = 255;
	while( index)
	{
		index = index - 1;
		count = 255;
		while( count)
			count = count - 1;
	}
}

clear()
{
	lights = 0x00;
	printf( "%d\n", lights);
	delay();
	return;
}

left()
{
	if( lights == 0x00)
	    lights = 0x10;
	else if( lights == 0x10)
	     lights = 0x30;
	else if( lights == 0x30)
	     lights = 0x70;
	else // if( lights == 0x70)
	     lights = 0x00;
	printf( "%d\n", lights);
	delay();
	return;
}

right()
{
	if( lights == 0x00)
	       lights = 0x08;
	else if( lights == 0x08)
	       lights = 0x0c;
	else if( lights == 0x0c)
	       lights = 0x0e;
	else // if( lights == 0x0e)
	       lights = 0x00;
	printf( "%d\n", lights);
	delay();
	return;
}

hazard()
{
	if( lights == 0x00)
	       lights = 0x7e;
	else // if( lights == 0x7e)
	       lights = 0x00;
	printf( "%d\n", lights);
	delay();
	return;
}

int	main()
{
	char	flags;
	while( 1)
	{
		if( flags & 0x01)
		    hazard();
		else if( flags & 0x02)
		    left();
		else if( flags & 0x04)
		    right();
		else 
		    clear();
	}
	return 0;
}
