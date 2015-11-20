
void introduction_to_the_app( void ) //start screen
{
	GtkWidget *label, *next_button, *body_frame;
	
	//create the main window for the aplication and set window properties
	main_window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_position( GTK_WINDOW( main_window), GTK_WIN_POS_CENTER );
	gtk_window_set_title( GTK_WINDOW( main_window), "Advanced Login Manager" );
	gtk_window_set_resizable( GTK_WINDOW( main_window), TRUE );
	gtk_window_resize( GTK_WINDOW( main_window), 700, 400 );
	g_signal_connect( GTK_OBJECT( main_window), "destroy", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );
	
	//craete the components for the introroduction page
	label = gtk_label_new( NULL );	//the text inside the body frame
	next_button = gtk_button_new_with_label( "NEXT" );	// NEXT button
	cancel_button = gtk_button_new_with_label( "CANCEL" );	//CANCEL button
	body_frame = gtk_frame_new( "Login manager setup wizard" );	//frame to hold the label
	main_table = gtk_table_new( 14, 12, TRUE );	//contains all other widgets
	
	//set the label text and insert it to the body frame
	gtk_label_set_markup( GTK_LABEL( label ), "<span fgcolor=\"black\" font=\"15\">Welcome to Advance Login Manager</span>" );
	gtk_container_add( GTK_CONTAINER(body_frame), label );
	
//	g_signal_connect( GTK_OBJECT( next_button), "clicked", GTK_SIGNAL_FUNC( show_terms_and_conditions ), NULL );
	g_signal_connect( GTK_OBJECT( next_button), "clicked", GTK_SIGNAL_FUNC( next_step ), NULL );
	g_signal_connect( GTK_OBJECT( cancel_button), "clicked", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );
	
	gtk_table_attach_defaults ( GTK_TABLE (main_table), next_button, 7, 9, 11, 12);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), cancel_button, 9, 11, 11, 12);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), body_frame, 1, 11, 1, 9);
	
	//add the main table to the main window
	gtk_container_add( GTK_CONTAINER( main_window), main_table );
	
	//display the main_window
	gtk_widget_show_all( main_window );
}



void next_step( void )
{
	gtk_widget_destroy( main_table);
		
	cancel_button = gtk_button_new_with_label( "ABORT" );
	body_frame = gtk_frame_new( NULL );
	main_table = gtk_table_new( 14, 12, TRUE );
	g_signal_connect( GTK_OBJECT( cancel_button), "clicked", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );
	gtk_table_attach_defaults ( GTK_TABLE (main_table), cancel_button, 9, 11, 11, 12);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), body_frame, 1, 11, 1, 10);
	gtk_container_add( GTK_CONTAINER( main_window), main_table );
	
	gtk_widget_show_all( main_window );
	installation_step_1();
}




