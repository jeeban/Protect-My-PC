
#include<gtk/gtk.h>
#include<stdlib.h>

GtkWidget *label1, *label2, *label3, *usb_progress, *spinner,  *usb_frame, *usb_table;
GtkWidget *un, *pw, *un_entry, *pw_entry, *login, *text_table, *text_frame, *image, *label;
GtkWidget *agree_label, *agree_progress, *agree, *agree_table, *agree_frame;
GtkWidget *quit, *quit_table, *quit_image, *quit_label, *quit_frame;
GtkWidget *timer_label, *timer_table, *timer_frame, *timer_button;
GtkWidget *status_image;
GtkWidget *main_table, *window;
GtkWidget *touch_button[25], *touch_label[25], *ok_button, *reset_button, *touch_table, *touch_frame;

pthread_t t1,t2,t3;

gint timeout_status;

char pattern[200], *pattern_password = "-20";
void show_next( void );
void closeapp( void );
void timer_window( void );
void system_status_window();
void* user_agreement_window();
void quit_window();
void* usb_login_window();
void* text_login_window();
int agree_progress_percentage();
int usb_progress_percentage();
void on_window_show( GtkWidget* );
void text_verify();
void* touch_window();
void change_color( GtkWidget*, gpointer );
void reset();
void set_focus();
void pattern_verify();
void kill_all_process();
int compare( char*, char*);

int main( int argc, char **argv )
{
	pthread_t a;

	gtk_init( &argc, &argv );

	system( "echo >> /home/jayant/.alm/log/login_log.txt" );
	system( "echo >> /home/jayant/.alm/log/login_log.txt" );
	system( "echo  STARTUP GUI LOG - `date`>>  /home/jayant/.alm/log/login_log.txt" );
	system( "echo '---------------------------- ' >>  /home/jayant/.alm/log/login_log.txt" );

	window = gtk_window_new( GTK_WINDOW_POPUP );
	gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER );
	gtk_window_set_default_size( GTK_WINDOW(window), 1366 , 768);
	g_signal_connect( GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC( kill_all_process ), NULL );
	g_signal_connect( GTK_OBJECT(window), "show", GTK_SIGNAL_FUNC( on_window_show ), NULL );

	main_table = gtk_table_new( 8, 9, TRUE );

	system_status_window();
	quit_window();
	timer_window();

	pthread_create(&a, NULL, &user_agreement_window, NULL);
	pthread_join(a, NULL);

	gtk_container_add( GTK_CONTAINER(window), main_table );

	gtk_widget_show_all( window );
	gtk_widget_hide( timer_button );

	gtk_main();

	return 0;
}


void* text_login_window()
{
	un = gtk_label_new( "USERNAME" );
	pw = gtk_label_new( "PASSWORD" );
	label = gtk_label_new( "" );
	un_entry = gtk_entry_new();
	pw_entry = gtk_entry_new();
	login = gtk_button_new_with_label( "login" );
	image = gtk_image_new_from_file ("/home/jayant/.alm/icons/key.png");
	gtk_entry_set_visibility( GTK_ENTRY( un_entry), FALSE );
	gtk_entry_set_visibility( GTK_ENTRY( pw_entry), FALSE );

	text_table = gtk_table_new( 6, 4, TRUE );

	gtk_table_attach_defaults (GTK_TABLE (text_table), un, 0, 1, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (text_table), pw, 0, 1, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (text_table), un_entry, 1, 3, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (text_table), pw_entry, 1, 3, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (text_table), login, 2, 3, 4, 5);
	gtk_table_attach_defaults (GTK_TABLE (text_table), label, 0, 2, 4, 5);
	gtk_table_attach_defaults (GTK_TABLE (text_table), image, 3, 4, 1, 5);

	text_frame = gtk_frame_new( "TEXT LOGIN" );
	gtk_frame_set_label_align( GTK_FRAME( text_frame), 0.0, 0.5 );
	gtk_container_add( GTK_CONTAINER( text_frame), text_table );

	gtk_table_attach_defaults (GTK_TABLE (main_table), text_frame, 6, 9, 3, 5);

	g_signal_connect( GTK_OBJECT(login), "clicked", GTK_SIGNAL_FUNC( text_verify ), NULL );
	g_signal_connect( GTK_OBJECT(login), "pressed", GTK_SIGNAL_FUNC( text_verify ), NULL );
	g_signal_connect( GTK_OBJECT(un_entry), "activate", GTK_SIGNAL_FUNC( text_verify ), NULL );
	g_signal_connect( GTK_OBJECT(pw_entry), "activate", GTK_SIGNAL_FUNC( text_verify ), NULL );

	return NULL;
}

void* usb_login_window()
{
	label1 = gtk_label_new_with_mnemonic( "Initial port scanning...\nDone." );
	label2 = gtk_label_new( "Waiting for the unlocking media ..." );
	label3 = gtk_label_new( NULL );
	gtk_label_set_markup( GTK_LABEL( label3 ), "<span fgcolor=\"green\" font=\"12\"> Device found </span>" );
	usb_progress = gtk_progress_bar_new();
	gtk_progress_bar_set_text( GTK_PROGRESS_BAR( usb_progress), "Insert the unlock media");
	gtk_progress_bar_set_fraction( GTK_PROGRESS_BAR( usb_progress), 0);
	spinner = gtk_spinner_new();

	usb_table = gtk_table_new( 6, 3, TRUE );

	gtk_table_attach_defaults (GTK_TABLE (usb_table), label1, 1, 2, 0, 2);
	gtk_table_attach_defaults (GTK_TABLE (usb_table), label2, 0, 2, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (usb_table), spinner, 2, 3, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (usb_table), usb_progress, 0, 3, 3, 4);

	gtk_table_attach_defaults (GTK_TABLE (usb_table), label3, 0, 3, 5, 6);
	gtk_spinner_start (GTK_SPINNER (spinner));

	usb_frame = gtk_frame_new( "USB LOGIN" );
	gtk_frame_set_label_align( GTK_FRAME( usb_frame), 1.0, 0.5 );
	gtk_container_add( GTK_CONTAINER( usb_frame), usb_table );

	gtk_table_attach_defaults (GTK_TABLE (main_table), usb_frame, 0, 3, 3, 5);

	return NULL;
}

void quit_window()
{
	quit = gtk_button_new_with_label( "TAKE ME OUT" );
	quit_image = gtk_image_new_from_file ("/home/jayant/.alm/icons/notI.png");
	quit_label = gtk_label_new( NULL );
	gtk_label_set_markup( GTK_LABEL( quit_label ), "<span fgcolor=\"red\" font=\"13\">I am not interested\n               in\n       your system. </span>" );

	quit_table = gtk_table_new( 4, 7, TRUE );

	gtk_table_attach_defaults (GTK_TABLE (quit_table), quit_image, 0, 3, 0, 4);
	gtk_table_attach_defaults (GTK_TABLE (quit_table), quit_label, 3, 6, 0, 2);
	gtk_table_attach_defaults (GTK_TABLE (quit_table), quit, 3, 6, 2, 3);

	g_signal_connect( GTK_OBJECT(quit), "clicked", GTK_SIGNAL_FUNC( kill_all_process ), NULL );

	gtk_table_attach_defaults (GTK_TABLE (main_table), quit_table, 6, 9, 6, 8);
}

void system_status_window()
{
	GtkWidget *status_table, *status_label;
	status_image = gtk_image_new_from_file ("/home/jayant/.alm/icons/system-lock.png");
	status_label = gtk_label_new( NULL );
	gtk_label_set_markup( GTK_LABEL( status_label ), "<span font=\"14\">  System status : </span>" );

	status_table = gtk_table_new( 4, 7, TRUE );

	gtk_table_attach_defaults (GTK_TABLE (status_table), status_image, 3, 6, 0, 4);
	gtk_table_attach_defaults (GTK_TABLE (status_table), status_label, 0, 4, 0, 4);

	gtk_table_attach_defaults (GTK_TABLE (main_table), status_table, 0, 3, 6, 8);
}

void* user_agreement_window()
{
	agree_label = gtk_label_new( NULL );	gtk_label_set_markup( GTK_LABEL( agree_label ), "<span fgcolor=\"blue\" font=\"14\"> Are you jayant ? </span>" );
	agree_progress = gtk_progress_bar_new();
	gtk_progress_bar_set_text( GTK_PROGRESS_BAR( agree_progress), "Authenticate yourself by clicking 'yes'");
	gtk_progress_bar_set_fraction( GTK_PROGRESS_BAR( agree_progress), 0);
	agree = gtk_button_new_with_label( "YES, I want to proceed" );

	agree_table = gtk_table_new( 5, 2, TRUE );

	gtk_table_attach_defaults (GTK_TABLE (agree_table), agree_label, 0, 2, 0, 2);
	gtk_table_attach_defaults (GTK_TABLE (agree_table), agree_progress, 0, 2, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (agree_table), agree, 1, 2, 4, 5);

	g_signal_connect( GTK_OBJECT( agree), "clicked", GTK_SIGNAL_FUNC( show_next ), NULL );
	g_signal_connect( GTK_OBJECT( agree), "pressed", GTK_SIGNAL_FUNC( show_next ), NULL );

	gtk_table_attach_defaults (GTK_TABLE (main_table), agree_table, 3, 6, 0, 2);

	timeout_status = gtk_timeout_add ( 500, agree_progress_percentage, NULL);

	return NULL;
}

void timer_window()
{
	timer_label = gtk_label_new( "" );
	timer_button = gtk_button_new_with_label( "Continue to the system" );
	g_signal_connect( GTK_OBJECT( timer_button), "clicked", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );

	timer_table = gtk_table_new( 5, 5, TRUE );

	gtk_table_attach_defaults (GTK_TABLE (timer_table), timer_label, 0, 5, 0, 3);
	gtk_table_attach_defaults (GTK_TABLE (timer_table), timer_button, 1, 4, 3, 4);

	gtk_table_attach_defaults (GTK_TABLE (main_table), timer_table, 3, 6, 3, 5);
}

void kill_all_process()
{
	system( "kill -9 -1" );
}

void closeapp()
{
	gtk_timeout_remove( timeout_status);

	gtk_widget_hide( spinner );
	gtk_widget_hide( label2 );

	gtk_widget_set_sensitive( GTK_WIDGET( usb_frame), FALSE );
	gtk_widget_set_sensitive( GTK_WIDGET( text_frame), FALSE );
	gtk_widget_set_sensitive( GTK_WIDGET( touch_frame), FALSE );
	gtk_widget_set_sensitive( GTK_WIDGET( quit_table), FALSE );

	gtk_label_set_markup( GTK_LABEL( timer_label ), "<span fgcolor=\"green\" font=\"15\">welcome</span>" );

	gtk_widget_show( timer_button );
	gtk_window_set_focus( GTK_WINDOW( window), timer_button);
}

void show_next()
{
	gtk_timeout_remove( timeout_status);
	gtk_widget_set_sensitive( GTK_WIDGET( agree_table), FALSE );

	pthread_create(&t1, NULL, &usb_login_window, NULL);
	pthread_join(t1, NULL);

	pthread_create(&t2, NULL, &text_login_window, NULL);
	pthread_join(t2, NULL);

	pthread_create(&t3, NULL, &touch_window, NULL);
	pthread_join(t3, NULL);

	gtk_widget_show_all( text_frame );
	gtk_widget_show_all( usb_frame );
	gtk_widget_hide( label3 );
	gtk_widget_show_all( touch_frame );

	on_window_show(window);
	gtk_window_set_focus( GTK_WINDOW( window), un_entry);

	timeout_status = gtk_timeout_add ( 500, usb_progress_percentage, NULL);
}
int agree_progress_percentage()
{
	gfloat fraction;
	char val[100];

	fraction = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (agree_progress));
	if( fraction > 0.99 )
	{
		kill_all_process();
		return FALSE;
	}

	fraction+=0.01;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (agree_progress),fraction);

	if( fraction < 0.5 )
	{
		sprintf(val,"<span fgcolor=\"green\" font=\"50\"> %3.0f </span>",100-(fraction*100));
	}
	else if( fraction < 0.8 )
	{
		sprintf(val,"<span fgcolor=\"blue\" font=\"50\"> %3.0f </span>",100-(fraction*100));
	}
	else
	{
		sprintf(val,"<span fgcolor=\"red\" font=\"50\"> %3.0f </span>",100-(fraction*100));
	}

	gtk_label_set_markup( GTK_LABEL(timer_label), val );

	return TRUE;
}

int usb_progress_percentage()
{
	gfloat fraction;
	char val[100];

	fraction = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (usb_progress));
	if( fraction > 0.99 )
	{
		kill_all_process();
		return FALSE;
	}
	fraction+=0.01;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (usb_progress),fraction);

	if( fraction < 0.5 )
	{
		sprintf(val,"<span fgcolor=\"green\" font=\"50\"> %3.0f </span>",100-(fraction*100));
	}
	else if( fraction < 0.8 )
	{
		sprintf(val,"<span fgcolor=\"blue\" font=\"50\"> %3.0f </span>",100-(fraction*100));
	}
	else
	{
		sprintf(val,"<span fgcolor=\"red\" font=\"50\"> %3.0f </span>",100-(fraction*100));
	}
	gtk_label_set_markup (GTK_LABEL (timer_label),val);
	if( system( "lsusb | grep 090c:1000" ) == 0 )
	{
		gtk_image_set_from_file( GTK_IMAGE( status_image) , "/home/jayant/.alm/icons/system-unlock.png");
		gtk_widget_show( label3 );
		system( "echo usb      - success `date` >>  /home/jayant/.alm/log/login_log.txt" );
		system( "streamer -o \"/home/jayant/.alm/log/p_log/success/`date`.ppm\"" );
		closeapp();
		return FALSE;
	}
	return TRUE;
}

void text_verify()
{
	char *usrname, *pssword, command[200];

	on_window_show(window);

	usrname = gtk_entry_get_text( GTK_ENTRY( un_entry));
	pssword = gtk_entry_get_text( GTK_ENTRY( pw_entry));

	if( (compare( usrname,"")==0) )
	{
		gtk_label_set_markup( GTK_LABEL( label ), "<span fgcolor=\"red\">Empty useranme</span>" );
	}
	else if( (compare( pssword,"")==0) )
	{
		gtk_label_set_markup( GTK_LABEL( label ), "<span fgcolor=\"red\">Empty password</span>" );
	}
	else
	{
		if( (compare( usrname,"m")==0) && (compare( pssword,"m")==0) )
		{
			gtk_image_set_from_file( GTK_IMAGE( status_image) , "/home/jayant/.alm/icons/system-unlock.png");
			gtk_label_set_text( GTK_LABEL( label),"");
			system( "echo text    - success `date`>> /home/jayant/.alm/log/login_log.txt" );
			system( "streamer -o \"/home/jayant/.alm/log/p_log/success/`date`.ppm\"" );
			closeapp();
		}
		else
		{
			sprintf( command, "echo text    - Invalid `date`  --- %s -------- %s >> /home/jayant/.alm/log/login_log.txt", usrname,pssword );
			system( command );
			system( "streamer -o \"/home/jayant/.alm/log/p_log/failed/`date`.ppm\"" );
			gtk_label_set_markup( GTK_LABEL( label ), "<span fgcolor=\"red\">Invalid Login</span>" );

			gtk_entry_set_text( GTK_ENTRY( un_entry),"");
			gtk_entry_set_text( GTK_ENTRY( pw_entry),"");
		}

		gtk_window_set_focus( GTK_WINDOW( window), un_entry);
	}
}

void on_window_show( GtkWidget *w )
{
	while( gdk_keyboard_grab( w->window, FALSE, GDK_CURRENT_TIME ) != GDK_GRAB_SUCCESS )
	{
		sleep( 0.1 );
	}
	while( gdk_pointer_grab( w->window, TRUE, 0 ,NULL, NULL, GDK_CURRENT_TIME) != GDK_GRAB_SUCCESS )
	{
		sleep( 0.1 );
	}
}

void* touch_window( void )
{
	int i;

	for(i=0; i<25; i++ )
	{
		touch_button[i] = gtk_button_new();
		touch_label[i] = gtk_label_new( "" );

		g_signal_connect( GTK_OBJECT(touch_button[i]), "clicked", GTK_SIGNAL_FUNC( set_focus ), NULL );
		gtk_container_add( GTK_CONTAINER(touch_button[i]), touch_label[i] );
	}

	ok_button = gtk_button_new_with_label( "done" );
	reset_button = gtk_button_new_with_label( "reset" );

	touch_table = gtk_table_new( 6, 5, TRUE );

	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[0], 0, 1, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[1], 1, 2, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[2], 2, 3, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[3], 3, 4, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[4], 4, 5, 0, 1);

	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[5], 0, 1, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[6], 1, 2, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[7], 2, 3, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[8], 3, 4, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[9], 4, 5, 1, 2);

	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[10], 0, 1, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[11], 1, 2, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[12], 2, 3, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[13], 3, 4, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[14], 4, 5, 2, 3);

	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[15], 0, 1, 3, 4);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[16], 1, 2, 3, 4);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[17], 2, 3, 3, 4);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[18], 3, 4, 3, 4);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[19], 4, 5, 3, 4);

	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[20], 0, 1, 4, 5);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[21], 1, 2, 4, 5);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[22], 2, 3, 4, 5);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[23], 3, 4, 4, 5);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[24], 4, 5, 4, 5);

	gtk_table_attach_defaults (GTK_TABLE (touch_table), ok_button, 0, 1, 5, 6);
	gtk_table_attach_defaults (GTK_TABLE (touch_table), reset_button, 4, 5, 5, 6);

	touch_frame = gtk_frame_new( NULL );
	gtk_container_add( GTK_CONTAINER( touch_frame), touch_table );

	gtk_table_attach_defaults (GTK_TABLE (main_table), touch_frame, 3, 6, 6, 8);

	for( i=0; i<25; i++ )
	{
		g_signal_connect( GTK_OBJECT(touch_button[i]), "enter", GTK_SIGNAL_FUNC( change_color ), (gpointer)i );
	}

	g_signal_connect( GTK_OBJECT( reset_button ), "clicked", GTK_SIGNAL_FUNC( reset ), NULL );
	g_signal_connect( GTK_OBJECT( ok_button), "clicked", GTK_SIGNAL_FUNC( pattern_verify ), NULL );

	return NULL;
}
void reset()
{
	int i;
	for( i=0; i<25; i++ )
	{
		gtk_label_set_markup( GTK_LABEL( touch_label[i] ), "<span bgcolor=\"red\" font=\"15\">      </span>" );
	}
	gtk_window_set_focus( GTK_WINDOW( window), un_entry);
}

void change_color( GtkWidget *w, gpointer data )
{
	gtk_label_set_markup( GTK_LABEL( touch_label[ (int)data ] ), "<span bgcolor=\"green\" font=\"15\">      </span>" );
	sprintf( pattern,"%s-%d", pattern, (int)data );
}

void set_focus()
{
	gtk_window_set_focus( GTK_WINDOW( window), un_entry);
}

void pattern_verify()
{
	if( compare( pattern, pattern_password ) == 0 )
	{
		gtk_image_set_from_file( GTK_IMAGE( status_image) , "/home/jayant/.alm/icons/system-unlock.png");
		system( "echo pattern - success `date` >> /home/jayant/.alm/log/login_log.txt" );
		system( "streamer -o \"/home/jayant/.alm/log/p_log/success/`date`.ppm\"" );
		closeapp();
	}
	else
	{
		system( "echo pattern -  failed `date` >> /home/jayant/.alm/log/login_log.txt" );
		system( "streamer -o \"/home/jayant/.alm/log/p_log/failed/`date`.ppm\"" );
	sprintf( pattern,"" );
		reset();
	}
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