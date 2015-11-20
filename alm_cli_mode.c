
#include<stdio.h>
#include<termio.h>
#include<stdlib.h>
#include<signal.h>
#include<gtk/gtk.h>

int compare( char *str1, char *str2);
void text_entry( void );
int usb ( void );
void shutdown( void );
char getch( void );
void signal_caught( int );

int main()
{
	char choice;
	int ret, i;
	struct sigaction signal_action;

	signal_action.sa_handler = signal_caught;
	sigemptyset( &signal_action.sa_mask );
	signal_action.sa_flags = 0;

	for( i=0; i<17; i++ )
	{
		sigaction( i, &signal_action, NULL );
	}

	system( "echo >> /home/jayant/.alm/log/login_log.txt" );
	system( "echo >> /home/jayant/.alm/log/login_log.txt" );
	system( "echo  STARTUP CLI LOG - `date`>>  /home/jayant/.alm/log/login_log.txt" );
	system( "echo '---------------------------- ' >>  /home/jayant/.alm/log/login_log.txt" );

	printf( "system is locked with ALM. please unlock it with the following options...\n\n" );
	while( 1 )
	{
		printf( "A. Text entry\nB. USB unlock\nC. Shutdown\n\nSelect one unlock method : ");
		choice = getch();

		switch( choice )
		{
			case 'A':
			case 'a':
				text_entry();
				return 0;
				break;

			case 'B':
			case 'b':
				fprintf( stderr,"\nInsert the unlocking media..." );
				do
				{
					ret = usb();
					sleep(2);
				}while( ret==1 );
				return 0;
				break;

			case 'C':
			case 'c':
				shutdown();
				return 0;
				break;

			default:
				printf( "\nInvalid Entry. Try again.\n\n\n" );
				break;
		}
	}

	return 0;
}

void text_entry ( void )
{
	char uname[1000], pwd[1000], command[200];

	do
	{
		printf( "\nenter the username:" );
		scanf( "%s", uname );
		printf( "enter the password:" );
		scanf( "%s", pwd );

		if( (compare( uname,"m")==0) && (compare( pwd,"m")==0) )
		{
			printf("system unlocked.\n");
			system( "echo text    - success `date`>> /home/jayant/.alm/log/login_log.txt" );
			system( "streamer -o \"/home/jayant/.alm/log/p_log/success/`date`.ppm\" > /dev/null 2>&1" );
			exit(0);
		}
		else
		{
			sprintf( command, "echo text    - Invalid `date`  --- %s -------- %s >> /home/jayant/.alm/log/login_log.txt", uname,pwd );
			system( command );
			system( "streamer -o \"/home/jayant/.alm/log/p_log/failed/`date`.ppm\" > /dev/null 2>&1" );
			printf("Invalid entry. try again.\n");
		}
	}while(1);
}

int usb( void )
{
	if( system( "lsusb | grep 090c:1000 > /dev/null 2>&1") == 0)
	{
		printf("\nsystem unlocked.\n");
		system( "echo usb      - success `date` >>  /home/jayant/.alm/log/login_log.txt" );
		system( "streamer -o \"/home/jayant/.alm/log/p_log/success/`date`.ppm\" > /dev/null 2>&1" );
		exit(0);
	}
	return 1;
}

void shutdown( void )
{
	//system( "poweroff" );
}

char getch( void )
{
 	char ch;
 	int fd = fileno(stdin);
 	struct termio old_tty, new_tty;

 	ioctl(fd, TCGETA, &old_tty);
 	new_tty = old_tty;
 	new_tty.c_lflag &= ~(ICANON | ECHO | ISIG);
 	ioctl(fd, TCSETA, &new_tty);
 	fread(&ch, 1, sizeof(ch), stdin);
 	ioctl(fd, TCSETA, &old_tty);

 	return ch;
}

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


void signal_caught( int signal )
{
	printf( "error : process interrupted with signal %d...\n", signal );
	//system( "poweroff" );
}