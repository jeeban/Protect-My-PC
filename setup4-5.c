
void register_pattern( void )
{
	
	int i;
	target = pattern;
	
	gtk_frame_set_label( GTK_FRAME( body_frame), "Installation step - 4/5 (register a pattern)" );
	
	for(i=0; i<25; i++ )
	{
		touch_button[i] = gtk_button_new();
		touch_label[i] = gtk_label_new("");
		
		gtk_container_add( GTK_CONTAINER(touch_button[i]), touch_label[i] );
	}
	
	ok_button = gtk_button_new_with_label( "Done" );
	reset_button = gtk_button_new_with_label( "reset" );
	pattern_label = gtk_label_new( "Draw a pattern" );
	
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
	gtk_table_attach_defaults (GTK_TABLE (touch_table), pattern_label, 1, 4, 5, 6);
	
	touch_frame = gtk_frame_new( NULL );
	gtk_container_add( GTK_CONTAINER( touch_frame), touch_table );
	
	gtk_table_attach_defaults ( GTK_TABLE (main_table), touch_frame, 2, 10, 2, 9);
	
	for( i=0; i<25; i++ )
	{
		g_signal_connect( GTK_OBJECT(touch_button[i]), "enter", GTK_SIGNAL_FUNC( change_color ), (gpointer)i );
	}
	
	g_signal_connect( GTK_OBJECT( reset_button ), "clicked", GTK_SIGNAL_FUNC( reset ), NULL );
	g_signal_connect( GTK_OBJECT( ok_button), "clicked", GTK_SIGNAL_FUNC( pattern_verify_and_save ), NULL );
	
	gtk_widget_show_all( main_window );
	
}






void reset( void )
{
	int i;
	for( i=0; i<25; i++ )
	{
		gtk_label_set_markup( GTK_LABEL( touch_label[i] ), "<span bgcolor=\"white\" font=\"11\">      </span>" );
	}
	sprintf( target,"%c", '\0' );
}







	
void change_color( GtkWidget *w, gpointer data )
{
	gtk_label_set_markup( GTK_LABEL( touch_label[ (int)data ] ), "<span bgcolor=\"green\" font=\"11\">      </span>" );
	sprintf( target,"%s-%d", target, (int)data );
}








void pattern_verify_and_save( void )
{
	int i=0;
	
	if( count == 0 )
	{
		gtk_label_set_text( GTK_LABEL( pattern_label), "Re-draw same pattern" );
		for( i=0; i<25; i++ )
		{
			gtk_label_set_markup( GTK_LABEL( touch_label[i] ), "<span bgcolor=\"white\" font=\"11\">      </span>" );
		}
		
		target = re_pattern;
		count++;
	}
	else
	{
		if( compare( pattern, re_pattern ) == 0  && ( compare( pattern, "" ) != 0 ) )
		{
			sprintf( final_pattern, "%s", pattern );
			gtk_widget_destroy( touch_table );
			gtk_widget_destroy( touch_frame );
			start_final_installation();
		}
		else
		{
			
			count = 0;
			for( i=0; i<25; i++ )
			{
				gtk_label_set_markup( GTK_LABEL( touch_label[i] ), "<span bgcolor=\"white\" font=\"11\">      </span>" );
			}
			gtk_label_set_text( GTK_LABEL( pattern_label), "Pattern mismatch, Draw again" );
			sprintf( pattern,"%c", '\0' );
			sprintf( re_pattern,"%c", '\0' );
			target = pattern;
		}
	}
}
