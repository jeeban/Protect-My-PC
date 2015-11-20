void installation_step_1( void )
{
	install_status = 0;
	
	gtk_window_set_title( GTK_WINDOW( main_window), "Advanced Login Manager( Installation )" );
	
	gtk_widget_destroy( install_button );
	gtk_widget_destroy( unlock_button );
	gtk_frame_set_label( GTK_FRAME( body_frame), "Installation step - 1/5 (select an username)" );
	
	label[0] = gtk_label_new( "Enter an username" );
	label[1] = gtk_label_new( "Re-enter username" );
	entry[0] = gtk_entry_new();
	entry[1] = gtk_entry_new();
	next_button = gtk_button_new_with_label( "Done" );
	status_label = gtk_label_new( "" );
	
	gtk_table_attach_defaults ( GTK_TABLE (main_table), label[0], 3, 6, 4, 5);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), entry[0], 6, 9, 4, 5);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), label[1], 3, 6, 5, 6);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), entry[1], 6, 9, 5, 6);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), next_button, 7, 10, 8, 9);
	gtk_table_attach_defaults ( GTK_TABLE (main_table), status_label, 3, 9, 7, 8);
	
	g_signal_connect( GTK_OBJECT( next_button), "clicked", GTK_SIGNAL_FUNC( go_next ), NULL );
	g_signal_connect( GTK_OBJECT(entry[0]), "activate", GTK_SIGNAL_FUNC( go_next ), NULL );
	g_signal_connect( GTK_OBJECT(entry[1]), "activate", GTK_SIGNAL_FUNC( go_next ), NULL );
	
	gtk_widget_grab_focus( entry[0] );
	
	gtk_widget_show_all( main_window );
}




void go_next( void )
{
	char *temp;
	
	if( install_status == 0 )
	{
		
		temp = gtk_entry_get_text( GTK_ENTRY( entry[0] ));
		if( compare( temp, (char*)gtk_entry_get_text( GTK_ENTRY( entry[1] ) )) == 0 && (compare( temp, "") != 0 ) )
		{
			sprintf( username, "%s", temp );
			install_status = 1;
			gtk_frame_set_label( GTK_FRAME( body_frame), "Installation step - 2/5 (select a password)" );
			gtk_label_set_text( GTK_LABEL( label[0]), "Enter a password " );
			gtk_label_set_text( GTK_LABEL( label[1]), "Re-enter password" );
			gtk_entry_set_text( GTK_ENTRY( entry[0] ), "");
			gtk_entry_set_text( GTK_ENTRY( entry[1] ), "");
			gtk_label_set_text( GTK_LABEL( status_label), "" );
			gtk_widget_grab_focus( entry[0] );
			gtk_entry_set_visibility( GTK_ENTRY( entry[0]), FALSE );
			gtk_entry_set_visibility( GTK_ENTRY( entry[1]), FALSE );
		}
		else
		{
			gtk_entry_set_text( GTK_ENTRY( entry[0] ), "");
			gtk_entry_set_text( GTK_ENTRY( entry[1] ), "");
			gtk_label_set_markup( GTK_LABEL( status_label ), "<span fgcolor=\"red\" font=\"11\">Entry mismatch.</span>" );
			gtk_widget_grab_focus( entry[0] );
		}
	}
	else
	{
		temp = gtk_entry_get_text( GTK_ENTRY( entry[0] ));
		if( compare( temp, (char*)gtk_entry_get_text( GTK_ENTRY( entry[1] ) )) == 0 && (compare( temp, "") != 0 ) )
		{
			sprintf( password, "%s", temp );
			gtk_widget_destroy( label[0] );
			gtk_widget_destroy( label[1] );
			gtk_widget_destroy( entry[0] );
			gtk_widget_destroy( entry[1] );
			gtk_widget_destroy( status_label );
			gtk_widget_destroy( next_button );
			
			usb_register();
			
		}
		else
		{
			gtk_entry_set_text( GTK_ENTRY( entry[0] ), "");
			gtk_entry_set_text( GTK_ENTRY( entry[1] ), "");
			gtk_label_set_markup( GTK_LABEL( status_label ), "<span fgcolor=\"red\" font=\"11\">Entry mismatch.</span>" );
			gtk_widget_grab_focus( entry[0] );
		}
	}
}
			
