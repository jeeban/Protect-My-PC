
#include<stdio.h>
#include<stdlib.h>

int compare( char *str1, char *str2)
{
	char *ptr1, *ptr2;
	for( ptr1=str1, ptr2=str2; (*(ptr1) != '\0')	|| (*(ptr2) != '\0');  ptr1++, ptr2++  )
	{
		if( *(ptr1) != *(ptr2) )
		{
			return 1;
		}
	}
	return 0;
}

int main( int argc, char *argv[])
{
	if( argc < 2 )
	{
		return 0;
	}
	if( compare( argv[1], "gui") == 0 )
	{
		system( "sleep 3 && /home/`whoami`/.alm/scripts/alm_gui" );
		return 0;
	}
	else if( compare( argv[1], "interface") == 0 )
	{
		system( "/home/`whoami`/.alm/scripts/alm_interface" );
		return 0;
	}
	else if( compare( argv[1], "cli") == 0 )
	{
		system( "/home/`whoami`/.alm/scripts/alm_cli" );
		return 0;
	}
	return 0;
}