
#include<gtk/gtk.h>
#include<stdlib.h>
void showlog( void );
void verify_user( void );
void close_window_dialog( void );
void on_window_show( GtkWidget *w );
int compare( gchar *str1, char *str2);
void uninstall_confirmation( void );
void cancel_uninstall( void );
void uninstall( void );
void show_photo_log( void );
GtkWidget *main_window, *main_table;
GtkWidget *unlock_code;
GtkWidget *unlock_button, *close_button, *label, *popup_window;

int main( int argc, char **argv )
{

	gtk_init( &argc, &argv );

//	GtkWidget *logo;

	main_window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_position( GTK_WINDOW( main_window), GTK_WIN_POS_CENTER );
	gtk_window_set_title( GTK_WINDOW( main_window), "ALM log file viewer" );
	gtk_window_set_resizable( GTK_WINDOW( main_window), TRUE );
	gtk_window_resize( GTK_WINDOW( main_window), 700, 400 );
	g_signal_connect( GTK_OBJECT( main_window), "destroy", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );

	label = gtk_label_new( "Enter the unlock password to view the log  file." );
	unlock_code = gtk_entry_new();
	gtk_entry_set_visibility( GTK_ENTRY( unlock_code), FALSE );
	unlock_button = gtk_button_new_with_label( "Unlock" );
	close_button = gtk_button_new_with_label( "Close" );
//	logo = gtk_image_new_from_file ("trans.png");	// logo without text
	main_table = gtk_table_new( 14, 12, TRUE );	//contains all other widgets

	g_signal_connect( GTK_OBJECT( unlock_button), "clicked", GTK_SIGNAL_FUNC( verify_user ), NULL );
	g_signal_connect( GTK_OBJECT( close_button), "clicked", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );
	g_signal_connect( GTK_OBJECT( unlock_code), "activate", GTK_SIGNAL_FUNC( verify_user ), NULL );

	gtk_table_attach_defaults ( GTK_TABLE (main_table), label, 4, 8, 4, 5);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), unlock_code, 4, 8, 5, 6);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), unlock_button, 4, 8, 6, 7);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), close_button, 9, 11, 11, 12);
//	gtk_table_attach_defaults ( GTK_TABLE (main_table), logo, 1, 6, 10, 13);

	gtk_container_add( GTK_CONTAINER( main_window), main_table );
	gtk_widget_show_all( main_window );

	gtk_main();
	return 0;
}

void showlog( void )
{
	GtkWidget *photo_viewer_button, *uninstall_button, *body_frame, *textview, *scrolled_window;
	GtkTextBuffer *buffer;
	GtkTextIter iter;
  	GtkTextMark *mark;
  	char log[2000], ch, *ptr;
  	FILE *fp;

	gtk_widget_destroy( unlock_button);
	gtk_widget_destroy( close_button);
	gtk_widget_destroy( unlock_code);
	gtk_widget_destroy( label);

	photo_viewer_button = gtk_button_new_with_label( "photo-log" );	// NEXT button
	uninstall_button = gtk_button_new_with_label( "Uninstall" );	//CANCEL button
	body_frame = gtk_frame_new( "Advanced login Manager log file" );	//frame to hold the label

	gtk_table_attach_defaults ( GTK_TABLE (main_table), photo_viewer_button, 7, 9, 11, 12);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), uninstall_button, 9, 11, 11, 12);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), body_frame, 1, 11, 1, 10);

	g_signal_connect( GTK_OBJECT( uninstall_button), "clicked", GTK_SIGNAL_FUNC( uninstall_confirmation ), NULL );
	g_signal_connect( GTK_OBJECT( photo_viewer_button), "clicked", GTK_SIGNAL_FUNC( show_photo_log ), NULL );

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	textview = gtk_text_view_new ();
	gtk_widget_set_sensitive( GTK_WIDGET( textview), FALSE );
	gtk_container_add (GTK_CONTAINER (scrolled_window), textview);
	gtk_container_add (GTK_CONTAINER (body_frame), scrolled_window);
	buffer = gtk_text_view_get_buffer (textview);

	fp = fopen( "/home/jayant/.alm/log/login_log.txt", "r" );
	if( fp == NULL )
	{
		printf("error in opening log file." );
		exit(0);
	}
	ptr = &log[0];
	while( fscanf( fp, "%c", &ch ) && !feof(fp) )
	{
		if( ch == '\n' || ch == '\0')
		{
			*ptr = '\0';
			ptr = &log;

			gtk_text_buffer_get_end_iter (buffer, &iter);
			gtk_text_buffer_insert (buffer, &iter, "\n", -1);
			gtk_text_buffer_insert (buffer, &iter, log, -1);
			gtk_text_iter_set_line_offset (&iter, 0);
			mark = gtk_text_buffer_get_insert (buffer);
			gtk_text_buffer_move_mark (buffer, mark, &iter);
			gtk_text_view_scroll_mark_onscreen (textview, mark);
		}
		else
		{
			*ptr++ = ch;
		}
	}
	fclose(fp);
	gtk_widget_show_all( main_window );
}

void verify_user( void )
{
	if ( compare( (char*)gtk_entry_get_text( GTK_ENTRY( unlock_code )), "m" ) == 0 )
	{
		showlog();
	}
	else
	{
		gtk_window_set_focus( GTK_WINDOW( main_window), unlock_code);
	}
}

int compare( gchar *str1, char *str2)
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

void uninstall_confirmation( void )
{
	GtkWidget *popup_label, *popup_table, *popup_button[2];

	popup_window = gtk_window_new( GTK_WINDOW_POPUP );
	gtk_window_set_position( GTK_WINDOW( popup_window), GTK_WIN_POS_CENTER );
	gtk_window_set_resizable( GTK_WINDOW( popup_window), TRUE );
	gtk_window_set_default_size( GTK_WINDOW( popup_window), 300, 150 );
	g_signal_connect( GTK_OBJECT( popup_window), "destroy", GTK_SIGNAL_FUNC( gtk_widget_destroy ), popup_window );

	popup_label = gtk_label_new("");
	popup_button[0] = gtk_button_new_with_label( "Ok" );
	popup_button[1] = gtk_button_new_with_label( "Cancel" );
	gtk_label_set_markup( GTK_LABEL( popup_label ), "<span fgcolor=\"red\" font=\"13\">Do you want to uninstall ?</span>" );

	g_signal_connect( GTK_OBJECT( popup_button[0]), "clicked", GTK_SIGNAL_FUNC( uninstall ), NULL );
	g_signal_connect( GTK_OBJECT( popup_button[1]), "clicked", GTK_SIGNAL_FUNC( cancel_uninstall ), NULL );

	popup_table = gtk_table_new( 6, 6, TRUE );
	gtk_table_attach_defaults ( GTK_TABLE (popup_table), popup_label, 0, 6, 1, 3);
	gtk_table_attach_defaults ( GTK_TABLE (popup_table), popup_button[0], 1, 3, 3, 4);
	gtk_table_attach_defaults ( GTK_TABLE (popup_table), popup_button[1], 3, 5, 3, 4);

	gtk_container_add( GTK_CONTAINER( popup_window), popup_table );
	gtk_widget_show_all( popup_window );
}

void cancel_uninstall( void )
{
	gtk_widget_destroy( popup_window );
}

void uninstall( void )
{
	FILE *fp = fopen( "uninstall_alm.sh", "w" );
	fprintf( fp, "#!/bin/sh" );
	fprintf( fp, "\nrm -rf /home/`whoami`/.alm" );
	fprintf( fp, "\nrm /home/`whoami`/.config/autostart/alm.desktop" );
	fprintf( fp, "\n#gksu rm /bin/alm-run" );
	fclose(fp);
	system( "sh uninstall_alm.sh" );
	gtk_main_quit();
}

void show_photo_log( void )
{
	system( "xdg-open /home/`whoami`/.alm/log/p_log" );
}