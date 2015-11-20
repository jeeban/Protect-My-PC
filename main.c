

#include<gtk/gtk.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#include"headers.c"
#include"extra.c"

#include"intro.c"
#include"setup1&2-5.c"
#include"setup3-5.c"
#include"setup4-5.c"
#include"setup5-5.c"


int main( int argc, char **argv )
{
	
	if( getuid() == 0 )
	{	
		printf("Run the app as normal user and provide root password only when asked.\n");
		return 0;
	}
	
	gtk_init( &argc, &argv );
	introduction_to_the_app();
	gtk_main();
	
	return 0;
}	


