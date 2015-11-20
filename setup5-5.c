

void start_final_installation( void )
{
	gtk_frame_set_label( GTK_FRAME( body_frame), "Installation step - 5/5 ( managing source files )" );
	gtk_button_set_label( GTK_BUTTON( cancel_button), "Finish" );
	gtk_widget_set_sensitive( GTK_WIDGET( cancel_button), FALSE );
	pattern_label = gtk_label_new( "" );
	gtk_container_add( GTK_CONTAINER( body_frame), pattern_label );
	
	gtk_widget_show_all( main_window );
	
	fd = popen( "whoami", "r" );
	fscanf( fd, "%s", system_user_name );
	pclose(fd);
	
	create_directories();
	create_files();
	manage_files();
}



void create_directories( void )
{
	char foldername[200];
	
	sprintf( foldername, "/home/%s/.alm", system_user_name );
	mkdir( foldername, S_IRWXU );
	sprintf( foldername, "/home/%s/.alm/scripts", system_user_name );
	mkdir( foldername, S_IRWXU );
	sprintf( foldername, "/home/%s/.alm/icons", system_user_name );
	mkdir( foldername, S_IRWXU );
	sprintf( foldername, "/home/%s/.alm/log", system_user_name );
	mkdir( foldername, S_IRWXU );
	sprintf( foldername, "/home/%s/.alm/log/p_log", system_user_name );
	mkdir( foldername, S_IRWXU );
	sprintf( foldername, "/home/%s/.alm/log/p_log/success", system_user_name );
	mkdir( foldername, S_IRWXU );
	sprintf( foldername, "/home/%s/.alm/log/p_log/failed", system_user_name );
	mkdir( foldername, S_IRWXU );
}



void create_files( void )
{
	
	int i;
	int res_x, res_y;
	char *code[100];

	fd = popen( "xrandr | head -n 1 | cut -b 38-42", "r" );
	fscanf( fd, "%d", &res_x );
	pclose(fd);
	
	fd = popen( "xrandr | head -n 1 | cut -b 45-47", "r" );
	fscanf( fd, "%d", &res_y );
	pclose(fd);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	alm.desktop

	fd = fopen( "alm.desktop", "w" );
	fprintf( fd, "[Desktop Entry]\nName=alm_manager\nComment=advanced login manager\nExec=/bin/alm-run gui\nTerminal=false\nType=Application\nX-GNOME-Autostart-enabled=true" );
	fclose(fd);
	printf("alm.desktop created.\n");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	alm_gui_mode.c

	fd = fopen( "alm_gui_mode.c", "w" );
	
	code[0] = "#include<gtk/gtk.h>";
	code[1] = "#include<stdlib.h>";
	code[2] = "";
	code[3] = "GtkWidget *label1, *label2, *label3, *usb_progress, *spinner,  *usb_frame, *usb_table;";
	code[4] = "GtkWidget *un, *pw, *un_entry, *pw_entry, *login, *text_table, *text_frame, *image, *label;";
	code[5] = "GtkWidget *agree_label, *agree_progress, *agree, *agree_table, *agree_frame;";
	code[6] = "GtkWidget *quit, *quit_table, *quit_image, *quit_label, *quit_frame;";
	code[7] = "GtkWidget *timer_label, *timer_table, *timer_frame, *timer_button;";
	code[8] = "GtkWidget *status_image;";
	code[9] = "GtkWidget *main_table, *window;";
	code[10] = "GtkWidget *touch_button[25], *touch_label[25], *ok_button, *reset_button, *touch_table, *touch_frame;";
	code[11] = "";
	code[12] = "pthread_t t1,t2,t3;";
	code[13] = "";
	code[14] = "gint timeout_status;";
	code[15] = "";
	code[16] = "char pattern[200], *pattern_password = \"";

	for( i=0; i<17; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fprintf( fd, "%s\";", final_pattern );

	code[0] = "void show_next( void );";
	code[1] = "void closeapp( void );";
	code[2] = "void timer_window( void );";
	code[3] = "void system_status_window();";
	code[4] = "void* user_agreement_window();";
	code[5] = "void quit_window();",
	code[6] = "void* usb_login_window();";
	code[7] = "void* text_login_window();";
	code[8] = "int agree_progress_percentage();";
	code[9] = "int usb_progress_percentage();";
	code[10] = "void on_window_show( GtkWidget* );";
	code[11] = "void text_verify();";
	code[12] = "void* touch_window();";
	code[13] = "void change_color( GtkWidget*, gpointer );";
	code[14] = "void reset();";
	code[15] = "void set_focus();";
	code[16] = "void pattern_verify();";
	code[17] = "void kill_all_process();";
	code[18] = "int compare( char*, char*);";
	code[19] = "";
	code[20] = "int main( int argc, char **argv )";
	code[21] = "{";
	code[22] = "	pthread_t a;";
	code[23] = "";
	code[24] = "	gtk_init( &argc, &argv );";

	for( i=0; i<25; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\n\tsystem( \"echo >> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\tsystem( \"echo >> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\tsystem( \"echo  STARTUP GUI LOG - `date`>>  /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\tsystem( \"echo '---------------------------- ' >>  /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\n\twindow = gtk_window_new( GTK_WINDOW_POPUP );" );
	fprintf( fd, "\n\tgtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER );" );
	fprintf( fd, "\n\tgtk_window_set_default_size( GTK_WINDOW(window), %d , %d);", res_x, res_y );

	code[0] = "	g_signal_connect( GTK_OBJECT(window), \"destroy\", GTK_SIGNAL_FUNC( kill_all_process ), NULL );";
	code[1] = "	g_signal_connect( GTK_OBJECT(window), \"show\", GTK_SIGNAL_FUNC( on_window_show ), NULL );";
	code[2] = "";
	code[3] = "	main_table = gtk_table_new( 8, 9, TRUE );";
	code[4] = "";
	code[5] = "	system_status_window();";
	code[6] = "	quit_window();";
	code[7] = "	timer_window();";
	code[8] = "";
	code[9] = "	pthread_create(&a, NULL, &user_agreement_window, NULL);";
	code[10] = "	pthread_join(a, NULL);";
	code[11] = "";
	code[12] = "	gtk_container_add( GTK_CONTAINER(window), main_table );";
	code[13] = "";
	code[14] = "	gtk_widget_show_all( window );";
	code[15] = "	gtk_widget_hide( timer_button );";
	code[16] = "";
	code[17] = "	gtk_main();";
	code[18] = "";
	code[19] = "	return 0;";
	code[20] = "}";
	code[21] = "";
	code[22] = "";
	code[23] = "void* text_login_window()";
	code[24] = "{";	
	code[25] = "	un = gtk_label_new( \"USERNAME\" );";
	code[26] = "	pw = gtk_label_new( \"PASSWORD\" );";
	code[27] = "	label = gtk_label_new( \"\" );";
	code[28] = "	un_entry = gtk_entry_new();";
	code[29] = "	pw_entry = gtk_entry_new();";
	code[30] = "	login = gtk_button_new_with_label( \"login\" );";

	for( i=0; i<31; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\timage = gtk_image_new_from_file (\"/home/%s/.alm/icons/key.png\");", system_user_name );

	code[1] = "	gtk_entry_set_visibility( GTK_ENTRY( un_entry), FALSE );";
	code[2] = "	gtk_entry_set_visibility( GTK_ENTRY( pw_entry), FALSE );";
	code[3] = "";
	code[4] = "	text_table = gtk_table_new( 6, 4, TRUE );";
	code[5] = "";
	code[6] = "	gtk_table_attach_defaults (GTK_TABLE (text_table), un, 0, 1, 1, 2);";
	code[7] = "	gtk_table_attach_defaults (GTK_TABLE (text_table), pw, 0, 1, 2, 3);";
	code[8] = "	gtk_table_attach_defaults (GTK_TABLE (text_table), un_entry, 1, 3, 1, 2);";
	code[9] = "	gtk_table_attach_defaults (GTK_TABLE (text_table), pw_entry, 1, 3, 2, 3);";
	code[10] = "	gtk_table_attach_defaults (GTK_TABLE (text_table), login, 2, 3, 4, 5);";
	code[11] = "	gtk_table_attach_defaults (GTK_TABLE (text_table), label, 0, 2, 4, 5);";
	code[12] = "	gtk_table_attach_defaults (GTK_TABLE (text_table), image, 3, 4, 1, 5);";
	code[13] = "";
	code[14] = "	text_frame = gtk_frame_new( \"TEXT LOGIN\" );";
	code[15] = "	gtk_frame_set_label_align( GTK_FRAME( text_frame), 0.0, 0.5 );";
	code[16] = "	gtk_container_add( GTK_CONTAINER( text_frame), text_table );";
	code[17] = "";
	code[18] = "	gtk_table_attach_defaults (GTK_TABLE (main_table), text_frame, 6, 9, 3, 5);";
	code[19] = "";
	code[20] = "	g_signal_connect( GTK_OBJECT(login), \"clicked\", GTK_SIGNAL_FUNC( text_verify ), NULL );";
	code[21] = "	g_signal_connect( GTK_OBJECT(login), \"pressed\", GTK_SIGNAL_FUNC( text_verify ), NULL );";
	code[22] = "	g_signal_connect( GTK_OBJECT(un_entry), \"activate\", GTK_SIGNAL_FUNC( text_verify ), NULL );";
	code[23] = "	g_signal_connect( GTK_OBJECT(pw_entry), \"activate\", GTK_SIGNAL_FUNC( text_verify ), NULL );";
	code[24] = "";
	code[25] = "	return NULL;";
	code[26] = "}";
	code[27] = "";
	code[28] = "void* usb_login_window()";
	code[29] = "{";
	code[30] = "	label1 = gtk_label_new_with_mnemonic( \"Initial port scanning...\\nDone.\" );";
	code[31] = "	label2 = gtk_label_new( \"Waiting for the unlocking media ...\" );";
	code[32] = "	label3 = gtk_label_new( NULL );";
	code[33] = "	gtk_label_set_markup( GTK_LABEL( label3 ), \"<span fgcolor=\\\"green\\\" font=\\\"12\\\"> Device found </span>\" );";
	code[34] = "	usb_progress = gtk_progress_bar_new();";
	code[35] = "	gtk_progress_bar_set_text( GTK_PROGRESS_BAR( usb_progress), \"Insert the unlock media\");";
	code[36] = "	gtk_progress_bar_set_fraction( GTK_PROGRESS_BAR( usb_progress), 0);";
	code[37] = "	spinner = gtk_spinner_new();";
	code[38] = "";
	code[39] = "	usb_table = gtk_table_new( 6, 3, TRUE );";
	code[40] = "";
	code[41] = "	gtk_table_attach_defaults (GTK_TABLE (usb_table), label1, 1, 2, 0, 2);";
	code[42] = "	gtk_table_attach_defaults (GTK_TABLE (usb_table), label2, 0, 2, 2, 3);";
	code[43] = "	gtk_table_attach_defaults (GTK_TABLE (usb_table), spinner, 2, 3, 2, 3);";
	code[44] = "	gtk_table_attach_defaults (GTK_TABLE (usb_table), usb_progress, 0, 3, 3, 4);";
	code[45] = "";
	code[46] = "	gtk_table_attach_defaults (GTK_TABLE (usb_table), label3, 0, 3, 5, 6);";
	code[47] = "	gtk_spinner_start (GTK_SPINNER (spinner));";
	code[48] = "";
	code[49] = "	usb_frame = gtk_frame_new( \"USB LOGIN\" );";
	code[50] = "	gtk_frame_set_label_align( GTK_FRAME( usb_frame), 1.0, 0.5 );";
	code[51] = "	gtk_container_add( GTK_CONTAINER( usb_frame), usb_table );";
	code[52] = "";
	code[53] = "	gtk_table_attach_defaults (GTK_TABLE (main_table), usb_frame, 0, 3, 3, 5);";
	code[54] = "";
	code[55] = "	return NULL;";
	code[56] = "}";
	code[57] = "";
	code[58] = "void quit_window()";
	code[59] = "{";	
	code[60] = "	quit = gtk_button_new_with_label( \"TAKE ME OUT\" );";

	for( i=1; i<61; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\tquit_image = gtk_image_new_from_file (\"/home/%s/.alm/icons/notI.png\");", system_user_name );

	code[0] = "	quit_label = gtk_label_new( NULL );";
	code[1] = "	gtk_label_set_markup( GTK_LABEL( quit_label ), \"<span fgcolor=\\\"red\\\" font=\\\"13\\\">I am not interested\\n               in\\n       your system. </span>\" );";
	code[2] = "";
	code[3] = "	quit_table = gtk_table_new( 4, 7, TRUE );";
	code[4] = "";
	code[5] = "	gtk_table_attach_defaults (GTK_TABLE (quit_table), quit_image, 0, 3, 0, 4);";
	code[6] = "	gtk_table_attach_defaults (GTK_TABLE (quit_table), quit_label, 3, 6, 0, 2);";
	code[7] = "	gtk_table_attach_defaults (GTK_TABLE (quit_table), quit, 3, 6, 2, 3);";
	code[8] = "";
	code[9] = "	g_signal_connect( GTK_OBJECT(quit), \"clicked\", GTK_SIGNAL_FUNC( kill_all_process ), NULL );";
	code[10] = "";
	code[11] = "	gtk_table_attach_defaults (GTK_TABLE (main_table), quit_table, 6, 9, 6, 8);";
	code[12] = "}";
	code[13] = "";
	code[14] = "void system_status_window()";
	code[15] = "{";
	code[16] = "	GtkWidget *status_table, *status_label;";
	code[17] ="";
	
	for( i=0; i<18; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fprintf( fd, "	status_image = gtk_image_new_from_file (\"/home/%s/.alm/icons/system-lock.png\");", system_user_name ); 
	
	code[18] = "	status_label = gtk_label_new( NULL );";
	code[19] = "	gtk_label_set_markup( GTK_LABEL( status_label ), \"<span font=\\\"14\\\">  System status : </span>\" );";
	code[20] = "";
	code[21] = "	status_table = gtk_table_new( 4, 7, TRUE );";
	code[22] = "";
	code[23] = "	gtk_table_attach_defaults (GTK_TABLE (status_table), status_image, 3, 6, 0, 4);";
	code[24] = "	gtk_table_attach_defaults (GTK_TABLE (status_table), status_label, 0, 4, 0, 4);";
	code[25] = "";
	code[26] = "	gtk_table_attach_defaults (GTK_TABLE (main_table), status_table, 0, 3, 6, 8);";
	code[27] = "}";
	code[28] = "";
	code[29] = "void* user_agreement_window()";
	code[30] = "{";	
	code[31] = "	agree_label = gtk_label_new( NULL );";
	
	for( i=18; i<32; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fprintf( fd, "	gtk_label_set_markup( GTK_LABEL( agree_label ), \"<span fgcolor=\\\"blue\\\" font=\\\"14\\\"> Are you %s ? </span>\" );", system_user_name );
	
		
	code[15] = "	agree_progress = gtk_progress_bar_new();";
	code[16] = "	gtk_progress_bar_set_text( GTK_PROGRESS_BAR( agree_progress), \"Authenticate yourself by clicking 'yes'\");";
	code[17] = "	gtk_progress_bar_set_fraction( GTK_PROGRESS_BAR( agree_progress), 0);";
	code[18] = "	agree = gtk_button_new_with_label( \"YES, I want to proceed\" );";
	code[19] = "";
	code[20] = "	agree_table = gtk_table_new( 5, 2, TRUE );";
	code[21] = "";
	code[22] = "	gtk_table_attach_defaults (GTK_TABLE (agree_table), agree_label, 0, 2, 0, 2);";
	code[23] = "	gtk_table_attach_defaults (GTK_TABLE (agree_table), agree_progress, 0, 2, 2, 3);";
	code[24] = "	gtk_table_attach_defaults (GTK_TABLE (agree_table), agree, 1, 2, 4, 5);";
	code[25] = "";
	code[26] = "	g_signal_connect( GTK_OBJECT( agree), \"clicked\", GTK_SIGNAL_FUNC( show_next ), NULL );";
	code[27] = "	g_signal_connect( GTK_OBJECT( agree), \"pressed\", GTK_SIGNAL_FUNC( show_next ), NULL );";
	code[28] = "";
	code[29] = "	gtk_table_attach_defaults (GTK_TABLE (main_table), agree_table, 3, 6, 0, 2);";
	code[30] = "";
	code[31] = "	timeout_status = gtk_timeout_add ( 500, agree_progress_percentage, NULL);";
	code[32] = "";
	code[33] = "	return NULL;";
	code[34] = "}";	
	code[35] = "";
	code[36] = "void timer_window()";
	code[37] = "{";	
	code[38] = "	timer_label = gtk_label_new( \"\" );";
	code[39] = "	timer_button = gtk_button_new_with_label( \"Continue to the system\" );";
	code[40] = "	g_signal_connect( GTK_OBJECT( timer_button), \"clicked\", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );";
	code[41] = "";
	code[42] = "	timer_table = gtk_table_new( 5, 5, TRUE );";
	code[43] = "";
	code[44] = "	gtk_table_attach_defaults (GTK_TABLE (timer_table), timer_label, 0, 5, 0, 3);";
	code[45] = "	gtk_table_attach_defaults (GTK_TABLE (timer_table), timer_button, 1, 4, 3, 4);";
	code[46] = "";
	code[47] = "	gtk_table_attach_defaults (GTK_TABLE (main_table), timer_table, 3, 6, 3, 5);";
	code[48] = "}";	
	code[49] = "";
	code[50] = "void kill_all_process()";
	code[51] = "{";
	code[52] = "	system( \"kill -9 -1\" );";
	code[53] = "}";
	code[54] = "";
	code[55] = "void closeapp()";
	code[56] = "{";
	code[57] = "	gtk_timeout_remove( timeout_status);";
	code[58] = "";
	code[59] = "	gtk_widget_hide( spinner );";
	code[60] = "	gtk_widget_hide( label2 );";
	code[61] = "";
	code[62] = "	gtk_widget_set_sensitive( GTK_WIDGET( usb_frame), FALSE );";
	code[63] = "	gtk_widget_set_sensitive( GTK_WIDGET( text_frame), FALSE );";
	code[64] = "	gtk_widget_set_sensitive( GTK_WIDGET( touch_frame), FALSE );";
	code[65] = "	gtk_widget_set_sensitive( GTK_WIDGET( quit_table), FALSE );";
	code[66] = "";
	code[67] = "	gtk_label_set_markup( GTK_LABEL( timer_label ), \"<span fgcolor=\\\"green\\\" font=\\\"15\\\">welcome</span>\" );";
	code[68] = "";
	code[69] = "	gtk_widget_show( timer_button );";
	code[70] = "	gtk_window_set_focus( GTK_WINDOW( window), timer_button);";
	code[71] = "}";
	code[72] = "";
	code[73] = "void show_next()";
	code[74] = "{";
	code[75] = "	gtk_timeout_remove( timeout_status);";
	code[76] = "	gtk_widget_set_sensitive( GTK_WIDGET( agree_table), FALSE );";
	code[77] = "";
	code[78] = "	pthread_create(&t1, NULL, &usb_login_window, NULL);";
	code[79] = "	pthread_join(t1, NULL);";
	code[80] = "";
	code[81] = "	pthread_create(&t2, NULL, &text_login_window, NULL);";
	code[82] = "	pthread_join(t2, NULL);";
	code[83] = "";
	code[84] = "	pthread_create(&t3, NULL, &touch_window, NULL);";
	code[85] = "	pthread_join(t3, NULL);";
	code[86] = "";
	code[87] = "	gtk_widget_show_all( text_frame );";
	code[88] = "	gtk_widget_show_all( usb_frame );";
	code[89] = "	gtk_widget_hide( label3 );";
	code[90] = "	gtk_widget_show_all( touch_frame );";
	code[91] = "";
	code[92] = "	on_window_show(window);";
	code[93] = "	gtk_window_set_focus( GTK_WINDOW( window), un_entry);";
	code[94] = "";
	code[95] = "	timeout_status = gtk_timeout_add ( 500, usb_progress_percentage, NULL);";
	code[96] = "}";	

	for( i=15; i<97; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}


	code[0] = "int agree_progress_percentage()";
	code[1] = "{";
	code[2] = "	gfloat fraction;";
	code[3] = "	char val[100];";
	code[4] = "";
	code[5] = "	fraction = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (agree_progress));";
	code[6] = "	if( fraction > 0.99 )";
	code[7] = "	{";
	code[8] = "		kill_all_process();";
	code[9] = "		return FALSE;";
	code[10] = "	}";
	code[11] = "";
	code[12] = "	fraction+=0.01;";
	code[13] = "	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (agree_progress),fraction);";
	code[14] = "";
	code[15] = "	if( fraction < 0.5 )";
	code[16] = "	{";
	code[17] = "		sprintf(val,\"<span fgcolor=\\\"green\\\" font=\\\"50\\\"> %3.0f </span>\",100-(fraction*100));";
	code[18] = "	}";
	code[19] = "	else if( fraction < 0.8 )";
	code[20] = "	{";
	code[21] = "		sprintf(val,\"<span fgcolor=\\\"blue\\\" font=\\\"50\\\"> %3.0f </span>\",100-(fraction*100));";
	code[22] = "	}";
	code[23] = "	else";
	code[24] = "	{";
	code[25] = "		sprintf(val,\"<span fgcolor=\\\"red\\\" font=\\\"50\\\"> %3.0f </span>\",100-(fraction*100));";
	code[26] = "	}";
	code[27] = "";
	code[28] = "	gtk_label_set_markup( GTK_LABEL(timer_label), val );";
	code[29] = "";
	code[30] = "	return TRUE;";
	code[31] = "}";
	code[32] = "";
	code[33] = "int usb_progress_percentage()";
	code[34] = "{";
	code[35] = "	gfloat fraction;";
	code[36] = "	char val[100];";
	code[37] = "";
	code[38] = "	fraction = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (usb_progress));";
	code[39] = "	if( fraction > 0.99 )";
	code[40] = "	{";
	code[41] = "		kill_all_process();";
	code[42] = "		return FALSE;";
	code[43] = "	}";
	code[44] = "	fraction+=0.01;";
	code[45] = "	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (usb_progress),fraction);";
	code[46] = "";
	code[47] = "	if( fraction < 0.5 )";
	code[48] = "	{";
	code[49] = "		sprintf(val,\"<span fgcolor=\\\"green\\\" font=\\\"50\\\"> %3.0f </span>\",100-(fraction*100));";
	code[50] = "	}";
	code[51] = "	else if( fraction < 0.8 )";
	code[52] = "	{";
	code[53] = "		sprintf(val,\"<span fgcolor=\\\"blue\\\" font=\\\"50\\\"> %3.0f </span>\",100-(fraction*100));";
	code[54] = "	}";
	code[55] = "	else";
	code[56] = "	{";
	code[57] = "		sprintf(val,\"<span fgcolor=\\\"red\\\" font=\\\"50\\\"> %3.0f </span>\",100-(fraction*100));";
	code[58] = "	}";
	code[59] = "	gtk_label_set_markup (GTK_LABEL (timer_label),val);";

	for( i=0; i<60; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\tif( system( \"lsusb | grep %s\" ) == 0 )", usb );
	fprintf( fd, "\n\t{" );
	fprintf( fd, "\n\t	gtk_image_set_from_file( GTK_IMAGE( status_image) , \"/home/%s/.alm/icons/system-unlock.png\");", system_user_name );
	fprintf( fd, "\n\t	gtk_widget_show( label3 );" );
	fprintf( fd, "\n\t	system( \"echo usb      - success `date` >>  /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\t	system( \"streamer -o \\\"/home/%s/.alm/log/p_log/success/`date`.ppm\\\"\" );", system_user_name );


	code[0] = "		closeapp();";
	code[1] = "		return FALSE;";
	code[2] = "	}";
	code[3] = "	return TRUE;";
	code[4] = "}";
	code[5] = "";
	code[6] = "void text_verify()";
	code[7] = "{";
	code[8] = "	char *usrname, *pssword, command[200];";
	code[9] = "";	
	code[10] = "	on_window_show(window);";
	code[11] = "";
	code[12] = "	usrname = gtk_entry_get_text( GTK_ENTRY( un_entry));";
	code[13] = "	pssword = gtk_entry_get_text( GTK_ENTRY( pw_entry));";
	code[14] = "";
	code[15] = "	if( (compare( usrname,\"\")==0) )";
	code[16] = "	{";
	code[17] = "		gtk_label_set_markup( GTK_LABEL( label ), \"<span fgcolor=\\\"red\\\">Empty useranme</span>\" );";
	code[18] = "	}";
	code[19] = "	else if( (compare( pssword,\"\")==0) )";
	code[20] = "	{";
	code[21] = "		gtk_label_set_markup( GTK_LABEL( label ), \"<span fgcolor=\\\"red\\\">Empty password</span>\" );";
	code[22] = "	}";
	code[23] = "	else";
	code[24] = "	{";

	for( i=0; i<25; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\t\tif( (compare( usrname,\"%s\")==0) && (compare( pssword,\"%s\")==0) )", username, password );
	fprintf( fd, "\n\t\t{");
	fprintf( fd, "\n\t		gtk_image_set_from_file( GTK_IMAGE( status_image) , \"/home/%s/.alm/icons/system-unlock.png\");", system_user_name );
	fprintf( fd, "\n\t		gtk_label_set_text( GTK_LABEL( label),\"\");");
	fprintf( fd, "\n\t		system( \"echo text    - success `date`>> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\t		system( \"streamer -o \\\"/home/%s/.alm/log/p_log/success/`date`.ppm\\\"\" );", system_user_name );
	fprintf( fd, "\n\t		closeapp();");
	fprintf( fd, "\n\t	}");
	fprintf( fd, "\n\t	else");
	fprintf( fd, "\n\t	{");
	fprintf( fd, "\n\t		sprintf( command, \"echo text    - Invalid `date`  --- %%s -------- %%s >> /home/%s/.alm/log/login_log.txt\", usrname,pssword );", system_user_name );
	fprintf( fd, "\n\t		system( command );");
	fprintf( fd, "\n\t		system( \"streamer -o \\\"/home/%s/.alm/log/p_log/failed/`date`.ppm\\\"\" );", system_user_name );



	code[0] = "			gtk_label_set_markup( GTK_LABEL( label ), \"<span fgcolor=\\\"red\\\">Invalid Login</span>\" );";
	code[1] = "";
	code[2] = "			gtk_entry_set_text( GTK_ENTRY( un_entry),\"\");";
	code[3] = "			gtk_entry_set_text( GTK_ENTRY( pw_entry),\"\");";
	code[4] = "		}";
	code[5] = "";
	code[6] = "		gtk_window_set_focus( GTK_WINDOW( window), un_entry);";
	code[7] = "	}";
	code[8] = "}";
	code[9] = "";
	code[10] = "void on_window_show( GtkWidget *w )";
	code[11] = "{";
	code[12] = "	while( gdk_keyboard_grab( w->window, FALSE, GDK_CURRENT_TIME ) != GDK_GRAB_SUCCESS )";
	code[13] = "	{";
	code[14] = "		sleep( 0.1 );";
	code[15] = "	}";
	code[16] = "	while( gdk_pointer_grab( w->window, TRUE, 0 ,NULL, NULL, GDK_CURRENT_TIME) != GDK_GRAB_SUCCESS )";
	code[17] = "	{";
	code[18] = "		sleep( 0.1 );";
	code[19] = "	}";
	code[20] = "}";
	code[21] = "";
	code[22] = "void* touch_window( void )";
	code[23] = "{";
	code[24] = "	int i;";
	code[25] = "";
	code[26] = "	for(i=0; i<25; i++ )";
	code[27] = "	{";
	code[28] = "		touch_button[i] = gtk_button_new();";
	code[29] = "		touch_label[i] = gtk_label_new( \"\" );";
	code[30] = "";
	code[31] = "		g_signal_connect( GTK_OBJECT(touch_button[i]), \"clicked\", GTK_SIGNAL_FUNC( set_focus ), NULL );";
	code[32] = "		gtk_container_add( GTK_CONTAINER(touch_button[i]), touch_label[i] );";
	code[33] = "	}";
	code[34] = "";	
	code[35] = "	ok_button = gtk_button_new_with_label( \"done\" );";
	code[36] = "	reset_button = gtk_button_new_with_label( \"reset\" );";
	code[37] = "";
	code[38] = "	touch_table = gtk_table_new( 6, 5, TRUE );";
	code[39] = "";
	code[40] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[0], 0, 1, 0, 1);";
	code[41] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[1], 1, 2, 0, 1);";
	code[42] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[2], 2, 3, 0, 1);";
	code[43] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[3], 3, 4, 0, 1);";
	code[44] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[4], 4, 5, 0, 1);";
	code[45] = "";	
	code[46] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[5], 0, 1, 1, 2);";
	code[47] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[6], 1, 2, 1, 2);";
	code[48] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[7], 2, 3, 1, 2);";
	code[49] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[8], 3, 4, 1, 2);";
	code[50] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[9], 4, 5, 1, 2);";
	code[51] = "";
	code[52] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[10], 0, 1, 2, 3);";
	code[53] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[11], 1, 2, 2, 3);";
	code[54] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[12], 2, 3, 2, 3);";
	code[55] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[13], 3, 4, 2, 3);";
	code[56] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[14], 4, 5, 2, 3);";
	code[57] = "";	
	code[58] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[15], 0, 1, 3, 4);";
	code[59] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[16], 1, 2, 3, 4);";
	code[60] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[17], 2, 3, 3, 4);";
	code[61] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[18], 3, 4, 3, 4);";
	code[62] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[19], 4, 5, 3, 4);";
	code[63] = "";
	code[64] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[20], 0, 1, 4, 5);";
	code[65] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[21], 1, 2, 4, 5);";
	code[66] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[22], 2, 3, 4, 5);";
	code[67] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[23], 3, 4, 4, 5);";
	code[68] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), touch_button[24], 4, 5, 4, 5);";
	code[69] = "";
	code[70] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), ok_button, 0, 1, 5, 6);";
	code[71] = "	gtk_table_attach_defaults (GTK_TABLE (touch_table), reset_button, 4, 5, 5, 6);";
	code[72] = "";
	code[73] = "	touch_frame = gtk_frame_new( NULL );";
	code[74] = "	gtk_container_add( GTK_CONTAINER( touch_frame), touch_table );";
	code[75] = "";
	code[76] = "	gtk_table_attach_defaults (GTK_TABLE (main_table), touch_frame, 3, 6, 6, 8);";
	code[77] = "";
	code[78] = "	for( i=0; i<25; i++ )";
	code[79] = "	{";
	code[80] = "		g_signal_connect( GTK_OBJECT(touch_button[i]), \"enter\", GTK_SIGNAL_FUNC( change_color ), (gpointer)i );";
	code[81] = "	}";
	code[82] = "";
	code[83] = "	g_signal_connect( GTK_OBJECT( reset_button ), \"clicked\", GTK_SIGNAL_FUNC( reset ), NULL );";
	code[84] = "	g_signal_connect( GTK_OBJECT( ok_button), \"clicked\", GTK_SIGNAL_FUNC( pattern_verify ), NULL );";
	code[85] = "";
	code[86] = "	return NULL;";
	code[87] = "}";

	for( i=0; i<88; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}


	code[1] = "void reset()";
	code[2] = "{";
	code[3] = "	int i;";
	code[4] = "	for( i=0; i<25; i++ )";
	code[5] = "	{";
	code[6] = "		gtk_label_set_markup( GTK_LABEL( touch_label[i] ), \"<span bgcolor=\\\"red\\\" font=\\\"15\\\">      </span>\" );";
	code[7] = "	}";
	code[8] = "	gtk_window_set_focus( GTK_WINDOW( window), un_entry);";
	code[9] = "}";
	code[10] = "";
	code[11] = "void change_color( GtkWidget *w, gpointer data )";
	code[12] = "{";
	code[13] = "	gtk_label_set_markup( GTK_LABEL( touch_label[ (int)data ] ), \"<span bgcolor=\\\"green\\\" font=\\\"15\\\">      </span>\" );";
	code[14] = "	sprintf( pattern,\"%s-%d\", pattern, (int)data );";
	code[15] = "}";
	code[16] = "";
	code[17] = "void set_focus()";
	code[18] = "{";
	code[19] = "	gtk_window_set_focus( GTK_WINDOW( window), un_entry);";
	code[20] = "}";
	code[21] = "";
	code[22] = "void pattern_verify()";
	code[23] = "{";
	code[24] = "	if( compare( pattern, pattern_password ) == 0 )";
	code[25] = "	{";

	for( i=1; i<26; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}


	fprintf( fd, "\n\t	gtk_image_set_from_file( GTK_IMAGE( status_image) , \"/home/%s/.alm/icons/system-unlock.png\");", system_user_name );
	fprintf( fd, "\n\t	system( \"echo pattern - success `date` >> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\t	system( \"streamer -o \\\"/home/%s/.alm/log/p_log/success/`date`.ppm\\\"\" );", system_user_name );
	fprintf( fd, "\n\t	closeapp();");
	fprintf( fd, "\n\t}");
	fprintf( fd, "\n\telse");
	fprintf( fd, "\n\t{");
	fprintf( fd, "\n\t	system( \"echo pattern -  failed `date` >> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\t	system( \"streamer -o \\\"/home/%s/.alm/log/p_log/failed/`date`.ppm\\\"\" );", system_user_name );


	code[0] = "	sprintf( pattern,\"\" );";
	code[1] = "		reset();";
	code[2] = "	}";
	code[3] = "}";
	code[4] = "";
	code[5] = "int compare( char *str1, char *str2)";
	code[6] = "{";
	code[7] = "	char *ptr1, *ptr2;";
	code[8] = "	for( ptr1=str1, ptr2=str2; (*(ptr1) != '\\0')	|| (*(ptr2) != '\\0');  ptr1++, ptr2++  )";
	code[9] = "	{";
	code[10] = "		if( *(ptr1) != *(ptr2) )";
	code[11] = "		{";
	code[12] = "			return 1;";
	code[13] = "		}";
	code[14] = "	}";
	code[15] = "	return 0;";
	code[16] = "}";

	for( i=0; i<17; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fclose(fd);	
	printf("alm_gui_mode.c created.\n");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	alm_cli_mode.c

	fd = fopen( "alm_cli_mode.c", "w" );

	code[0] = "#include<stdio.h>";
	code[1] = "#include<termio.h>";
	code[2] = "#include<stdlib.h>";
	code[3] = "#include<signal.h>";
	code[4] = "#include<gtk/gtk.h>";
	code[5] = "";
	code[6] = "int compare( char *str1, char *str2);";
	code[7] = "void text_entry( void );";
	code[8] = "int usb ( void );";
	code[9] = "void shutdown( void );";
	code[10] = "char getch( void );";
	code[11] = "void signal_caught( int );";
	code[12] = "";
	code[13] = "int main()";
	code[14] = "{";
	code[15] = "	char choice;";
	code[16] = "	int ret, i;";
	code[17] = "	struct sigaction signal_action;";
	code[18] = "";
	code[19] = "	signal_action.sa_handler = signal_caught;";
	code[20] = "	sigemptyset( &signal_action.sa_mask );";
	code[21] = "	signal_action.sa_flags = 0;";
	code[22] = "";
	code[23] = "	for( i=0; i<17; i++ )";
	code[24] = "	{";
	code[25] = "		sigaction( i, &signal_action, NULL );";
	code[26] = "	}";
	code[27] = "";

	for( i=0; i<28; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\tsystem( \"echo >> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\tsystem( \"echo >> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\tsystem( \"echo  STARTUP CLI LOG - `date`>>  /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\tsystem( \"echo '---------------------------- ' >>  /home/%s/.alm/log/login_log.txt\" );", system_user_name );


	code[0] = "	printf( \"system is locked with ALM. please unlock it with the following options...\\n\\n\" );";
	code[1] = "	while( 1 )";
	code[2] = "	{";
	code[3] = "		printf( \"A. Text entry\\nB. USB unlock\\nC. Shutdown\\n\\nSelect one unlock method : \");";
	code[4] = "		choice = getch();";
	code[5] = "";
	code[6] = "		switch( choice )";
	code[7] = "		{";
	code[8] = "			case 'A':";
	code[9] = "			case 'a':";
	code[10] = "				text_entry();";
	code[11] = "				return 0;";
	code[12] = "				break;";
	code[13] = "";	
	code[14] = "			case 'B':";
	code[15] = "			case 'b':";
	code[16] = "				fprintf( stderr,\"\\nInsert the unlocking media...\" );";
	code[17] = "				do";
	code[18] = "				{";
	code[19] = "					ret = usb();";
	code[20] = "					sleep(2);";
	code[21] = "				}while( ret==1 );";
	code[22] = "				return 0;";
	code[23] = "				break;";
	code[24] = "";			
	code[25] = "			case 'C':";
	code[26] = "			case 'c':";
	code[27] = "				shutdown();";
	code[28] = "				return 0;";
	code[29] = "				break;";
	code[30] = "";			
	code[31] = "			default:";
	code[32] = "				printf( \"\\nInvalid Entry. Try again.\\n\\n\\n\" );";
	code[33] = "				break;";
	code[34] = "		}";
	code[35] = "	}";
	code[36] = "";
	code[37] = "	return 0;";
	code[38] = "}";
	code[39] = "";
	code[40] = "void text_entry ( void )";
	code[41] = "{";
	code[42] = "	char uname[1000], pwd[1000], command[200];";
	code[43] = "";
	code[44] = "	do";
	code[45] = "	{";
	code[46] = "		printf( \"\\nenter the username:\" );";
	code[47] = "		scanf( \"%s\", uname );";
	code[48] = "		printf( \"enter the password:\" );";
	code[49] = "		scanf( \"%s\", pwd );";
	code[50] = "";
 
	fprintf( fd, "\n" );
	for( i=0; i<51; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\t\tif( (compare( uname,\"%s\")==0) && (compare( pwd,\"%s\")==0) )", username, password );
	fprintf( fd, "\n\t\t{");
	fprintf( fd, "\n\t		printf(\"system unlocked.\\n\");");
	fprintf( fd, "\n\t		system( \"echo text    - success `date`>> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\t		system( \"streamer -o \\\"/home/%s/.alm/log/p_log/success/`date`.ppm\\\" > /dev/null 2>&1\" );", system_user_name );
	fprintf( fd, "\n\t		exit(0);");
	fprintf( fd, "\n\t	}");
	fprintf( fd, "\n\t	else");
	fprintf( fd, "\n\t	{");
	//fprintf( fd, "\n\t		system( \"echo text    - failed `date`>> /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\t		sprintf( command, \"echo text    - Invalid `date`  --- %%s -------- %%s >> /home/%s/.alm/log/login_log.txt\", uname,pwd );", system_user_name );
	fprintf( fd, "\n\t		system( command );");
	fprintf( fd, "\n\t		system( \"streamer -o \\\"/home/%s/.alm/log/p_log/failed/`date`.ppm\\\" > /dev/null 2>&1\" );", system_user_name );

	code[0] = "			printf(\"Invalid entry. try again.\\n\");";
	code[1] = "		}";
	code[2] = "	}while(1);";
	code[3] = "}";
	code[4] = "";
	code[5] = "int usb( void )";
	code[6] = "{";

	for( i=0; i<7; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	fprintf( fd, "\n\tif( system( \"lsusb | grep %s > /dev/null 2>&1\") == 0)", usb );
	fprintf( fd, "\n\t{" );
	fprintf( fd, "\n\t	printf(\"\\nsystem unlocked.\\n\");");
	fprintf( fd, "\n\t	system( \"echo usb      - success `date` >>  /home/%s/.alm/log/login_log.txt\" );", system_user_name );
	fprintf( fd, "\n\t	system( \"streamer -o \\\"/home/%s/.alm/log/p_log/success/`date`.ppm\\\" > /dev/null 2>&1\" );", system_user_name );
	fprintf( fd, "\n\t	exit(0);");


	code[0] = "	}";
	code[1] = "	return 1;";
	code[2] = "}";
	code[3] = "";
	code[4] = "void shutdown( void )";
	code[5] = "{";
	code[6] = "	//system( \"poweroff\" );";
	code[7] = "}";
	code[8] = "";
	code[9] = "char getch( void )";
	code[10] = "{";
	code[11] = " 	char ch;";
	code[12] = " 	int fd = fileno(stdin);";
	code[13] = " 	struct termio old_tty, new_tty;";
	code[14] = ""; 
	code[15] = " 	ioctl(fd, TCGETA, &old_tty);";
	code[16] = " 	new_tty = old_tty;";
	code[17] = " 	new_tty.c_lflag &= ~(ICANON | ECHO | ISIG);";
	code[18] = " 	ioctl(fd, TCSETA, &new_tty);";
	code[19] = " 	fread(&ch, 1, sizeof(ch), stdin);";
	code[20] = " 	ioctl(fd, TCSETA, &old_tty);";
	code[21] = ""; 
	code[22] = " 	return ch;";
	code[23] = "}";
	code[24] = "";
	code[25] = "int compare( char *str1, char *str2)";
	code[26] = "{";
	code[27] = "	char *ptr1, *ptr2;";
	code[28] = "	for( ptr1=str1, ptr2=str2; (*(ptr1) != '\\0')	|| (*(ptr2) != '\\0');  ptr1++, ptr2++  )";
	code[29] = "	{";
	code[30] = "		if( *(ptr1) != *(ptr2) )";
	code[31] = "		{";
	code[32] = "			return 1;";
	code[33] = "		}";
	code[34] = "	}";
	code[35] = "	return 0;";
	code[36] = "}\n\n";
	code[37] = "void signal_caught( int signal )";
	code[38] = "{";
	code[39] = "	printf( \"error : process interrupted with signal %d...\\n\", signal );";
	code[40] = "	//system( \"poweroff\" );";
	code[41] = "}";

	for( i=0; i<42; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}

	
	
	
	fclose(fd);
	printf("alm_cli_mode.c created.\n");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// alm_interface.c
	
	fd = fopen( "alm_interface.c", "w" );
	
	code[0] = "#include<gtk/gtk.h>";
	code[1] = "#include<stdlib.h>";
	code[2] = "void showlog( void );";
	code[3] = "void verify_user( void );";
	code[4] = "void close_window_dialog( void );";
	code[5] = "void on_window_show( GtkWidget *w );";
	code[6] = "int compare( gchar *str1, char *str2);";
	code[7] = "void uninstall_confirmation( void );";
	code[8] = "void cancel_uninstall( void );";
	code[9] = "void uninstall( void );";
	code[10] = "void show_photo_log( void );";
	code[11] = "GtkWidget *main_window, *main_table;";
	code[12] = "GtkWidget *unlock_code;";
	code[13] = "GtkWidget *unlock_button, *close_button, *label, *popup_window;";
	code[14] = "";
	code[15] = "int main( int argc, char **argv )";
	code[16] = "{";
	code[17] = "";
	code[18] = "	gtk_init( &argc, &argv );";
	code[19] = "";
	code[20] = "//	GtkWidget *logo;";
	code[21] = "";
	code[22] = "	main_window = gtk_window_new( GTK_WINDOW_TOPLEVEL );";
	code[23] = "	gtk_window_set_position( GTK_WINDOW( main_window), GTK_WIN_POS_CENTER );";
	code[24] = "	gtk_window_set_title( GTK_WINDOW( main_window), \"ALM log file viewer\" );";
	code[25] = "	gtk_window_set_resizable( GTK_WINDOW( main_window), TRUE );";
	code[26] = "	gtk_window_resize( GTK_WINDOW( main_window), 700, 400 );";
	code[27] = "	g_signal_connect( GTK_OBJECT( main_window), \"destroy\", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );";
	code[28] = "";
	code[29] = "	label = gtk_label_new( \"Enter the unlock password to view the log  file.\" );";
	code[30] = "	unlock_code = gtk_entry_new();";
	code[31] = "	gtk_entry_set_visibility( GTK_ENTRY( unlock_code), FALSE );";
	code[32] = "	unlock_button = gtk_button_new_with_label( \"Unlock\" );";
	code[33] = "	close_button = gtk_button_new_with_label( \"Close\" );";
	code[34] = "//	logo = gtk_image_new_from_file (\"trans.png\");	// logo without text";
	code[35] = "	main_table = gtk_table_new( 14, 12, TRUE );	//contains all other widgets";
	code[36] = "";
	code[37] = "	g_signal_connect( GTK_OBJECT( unlock_button), \"clicked\", GTK_SIGNAL_FUNC( verify_user ), NULL );";
	code[38] = "	g_signal_connect( GTK_OBJECT( close_button), \"clicked\", GTK_SIGNAL_FUNC( gtk_main_quit ), NULL );";
	code[39] = "	g_signal_connect( GTK_OBJECT( unlock_code), \"activate\", GTK_SIGNAL_FUNC( verify_user ), NULL );";
	code[40] = "";
	code[41] = "	gtk_table_attach_defaults ( GTK_TABLE (main_table), label, 4, 8, 4, 5);";
	code[42] = "	gtk_table_attach_defaults ( GTK_TABLE (main_table), unlock_code, 4, 8, 5, 6);";
	code[43] = "	gtk_table_attach_defaults ( GTK_TABLE (main_table), unlock_button, 4, 8, 6, 7);";
	code[44] = "	gtk_table_attach_defaults ( GTK_TABLE (main_table), close_button, 9, 11, 11, 12);";
	code[45] = "//	gtk_table_attach_defaults ( GTK_TABLE (main_table), logo, 1, 6, 10, 13);";
	code[46] = "";
	code[47] = "	gtk_container_add( GTK_CONTAINER( main_window), main_table );";
	code[48] = "	gtk_widget_show_all( main_window );";
	code[49] = "";
	code[50] = "	gtk_main();";
	code[51] = "	return 0;";
	code[52] = "}";
	code[53] = "";
	code[54] = "void showlog( void )";
	code[55] = "{";
	code[56] = "	GtkWidget *photo_viewer_button, *uninstall_button, *body_frame, *textview, *scrolled_window;";
	
	for( i=0; i<57; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	code[0] = "	GtkTextBuffer *buffer;";
	code[1] = "	GtkTextIter iter;";
	code[2] = "  	GtkTextMark *mark;";
	code[3] = "  	char log[2000], ch, *ptr;";
	code[4] = "  	FILE *fp;";
	code[5] = "";
	code[6] = "	gtk_widget_destroy( unlock_button);";
	code[7] = "	gtk_widget_destroy( close_button);";
	code[8] = "	gtk_widget_destroy( unlock_code);";
	code[9] = "	gtk_widget_destroy( label);";
	code[10] = "";
	code[11] = "	photo_viewer_button = gtk_button_new_with_label( \"photo-log\" );	// NEXT button";
	code[12] = "	uninstall_button = gtk_button_new_with_label( \"Uninstall\" );	//CANCEL button";
	code[13] = "	body_frame = gtk_frame_new( \"Advanced login Manager log file\" );	//frame to hold the label";
	code[14] = "";
	code[15] = "	gtk_table_attach_defaults ( GTK_TABLE (main_table), photo_viewer_button, 7, 9, 11, 12);";
	code[16] = "	gtk_table_attach_defaults ( GTK_TABLE (main_table), uninstall_button, 9, 11, 11, 12);";
	code[17] = "	gtk_table_attach_defaults ( GTK_TABLE (main_table), body_frame, 1, 11, 1, 10);";
	code[18] = "";
	code[19] = "	g_signal_connect( GTK_OBJECT( uninstall_button), \"clicked\", GTK_SIGNAL_FUNC( uninstall_confirmation ), NULL );";
	code[20] = "	g_signal_connect( GTK_OBJECT( photo_viewer_button), \"clicked\", GTK_SIGNAL_FUNC( show_photo_log ), NULL );";
	code[21] = "";
	code[22] = "	scrolled_window = gtk_scrolled_window_new (NULL, NULL);";
	code[23] = "	textview = gtk_text_view_new ();";
	code[24] = "	gtk_text_view_set_editable( GTK_TEXT_VIEW(textview), FALSE);";
	code[25] = "	gtk_container_add (GTK_CONTAINER (scrolled_window), textview);";
	code[26] = "	gtk_container_add (GTK_CONTAINER (body_frame), scrolled_window);";
	code[27] = "	buffer = gtk_text_view_get_buffer (textview);";
	code[28] = "";
	
	for( i=0; i<29; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fprintf( fd,"\n	fp = fopen( \"/home/%s/.alm/log/login_log.txt\", \"r\" );", system_user_name );
	
	code[0] = "	if( fp == NULL )";
	code[1] = "	{";
	code[2] = "		printf(\"error in opening log file.\" );";
	code[3] = "		exit(0);";
	code[4] = "	}";
	code[5] = "	ptr = &log[0];";
	code[6] = "	while( fscanf( fp, \"%c\", &ch ) && !feof(fp) )";
	code[7] = "	{";
	code[8] = "		if( ch == '\\n' || ch == '\\0')";
	code[9] = "		{";
	code[10] = "			*ptr = '\\0';";
	code[11] = "			ptr = &log;";
	code[12] = "";	
	code[13] = "			gtk_text_buffer_get_end_iter (buffer, &iter);";
	code[14] = "			gtk_text_buffer_insert (buffer, &iter, \"\\n\", -1);";
	code[15] = "			gtk_text_buffer_insert (buffer, &iter, log, -1);";
	code[16] = "			gtk_text_iter_set_line_offset (&iter, 0);";
	code[17] = "			mark = gtk_text_buffer_get_insert (buffer);";
	code[18] = "			gtk_text_buffer_move_mark (buffer, mark, &iter);";
	code[19] = "			gtk_text_view_scroll_mark_onscreen (textview, mark);";
	code[20] = "		}";
	code[21] = "		else";
	code[22] = "		{";
	code[23] = "			*ptr++ = ch;";
	code[24] = "		}";
	code[25] = "	}";
	code[26] = "	fclose(fp);";
	code[27] = "	gtk_widget_show_all( main_window );";
	code[28] = "}";
	code[29] = "";
	code[30] = "void verify_user( void )";
	code[31] = "{";
	
	for( i=0; i<32; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fprintf( fd, "\n\tif ( compare( (char*)gtk_entry_get_text( GTK_ENTRY( unlock_code )), \"%s\" ) == 0 )", password );
	
	
	code[0] = "	{";
	code[1] = "		showlog();";
	code[2] = "	}";
	code[3] = "	else";
	code[4] = "	{";
	code[5] = "		gtk_window_set_focus( GTK_WINDOW( main_window), unlock_code);";
	code[6] = "	}";
	code[7] = "}";
	code[8] = "";
	code[9] = "int compare( gchar *str1, char *str2)";
	code[10] = "{";
	code[11] = "	char *ptr1, *ptr2;";
	code[12] = "	for( ptr1=str1, ptr2=str2; (*(ptr1) != '\\0')	|| (*(ptr2) != '\\0');  ptr1++, ptr2++  )";
	code[13] = "	{";
	code[14] = "		if( *(ptr1) != *(ptr2) )";
	code[15] = "		{";
	code[16] = "			return 1;";
	code[17] = "		}";
	code[18] = "	}";
	code[19] = "	return 0;";
	code[20] = "}";
	code[21] = "";
	code[22] = "void uninstall_confirmation( void )";
	code[23] = "{";
	code[24] = "	GtkWidget *popup_label, *popup_table, *popup_button[2];";
	code[25] = "";
	code[26] = "	popup_window = gtk_window_new( GTK_WINDOW_POPUP );";
	code[27] = "	gtk_window_set_position( GTK_WINDOW( popup_window), GTK_WIN_POS_CENTER );";
	code[28] = "	gtk_window_set_resizable( GTK_WINDOW( popup_window), TRUE );";
	code[29] = "	gtk_window_set_default_size( GTK_WINDOW( popup_window), 300, 150 );";
	code[30] = "	g_signal_connect( GTK_OBJECT( popup_window), \"destroy\", GTK_SIGNAL_FUNC( gtk_widget_destroy ), popup_window );";
	code[31] = "";
	code[32] = "	popup_label = gtk_label_new(\"\");";
	code[33] = "	popup_button[0] = gtk_button_new_with_label( \"Ok\" );";
	code[34] = "	popup_button[1] = gtk_button_new_with_label( \"Cancel\" );";
	code[35] = "	gtk_label_set_markup( GTK_LABEL( popup_label ), \"<span fgcolor=\\\"red\\\" font=\\\"13\\\">Do you want to uninstall ?</span>\" );";
	code[36] = "";
	code[37] = "	g_signal_connect( GTK_OBJECT( popup_button[0]), \"clicked\", GTK_SIGNAL_FUNC( uninstall ), NULL );";
	code[38] = "	g_signal_connect( GTK_OBJECT( popup_button[1]), \"clicked\", GTK_SIGNAL_FUNC( cancel_uninstall ), NULL );";
	code[39] = "";
	code[40] = "	popup_table = gtk_table_new( 6, 6, TRUE );";
	code[41] = "	gtk_table_attach_defaults ( GTK_TABLE (popup_table), popup_label, 0, 6, 1, 3);";
	code[42] = "	gtk_table_attach_defaults ( GTK_TABLE (popup_table), popup_button[0], 1, 3, 3, 4);";
	code[43] = "	gtk_table_attach_defaults ( GTK_TABLE (popup_table), popup_button[1], 3, 5, 3, 4);";
	code[44] = "";
	code[45] = "	gtk_container_add( GTK_CONTAINER( popup_window), popup_table );";
	code[46] = "	gtk_widget_show_all( popup_window );";
	code[47] = "}";
	code[48] = "";
	code[49] = "void cancel_uninstall( void )";
	code[50] = "{";
	code[51] = "	gtk_widget_destroy( popup_window );";
	code[52] = "}";
	code[53] = "";
	
	
	code[54] = "void uninstall( void )";
	code[55] = "{";
	code[56] = "	FILE *fp = fopen( \"uninstall_alm.sh\", \"w\" );";
	code[57] = "	fprintf( fp, \"#!/bin/sh\" );";
	code[58] = "	fprintf( fp, \"\\nrm -rf /home/`whoami`/.alm\" );";
	code[59] = "	fprintf( fp, \"\\nrm /home/`whoami`/.config/autostart/alm.desktop\" );";
	code[60] = "	fprintf( fp, \"\\n#gksu rm /bin/alm-run\" );";
	code[61] = "	fclose(fp);";
	code[62] = "	system( \"sh uninstall_alm.sh\" );";
	code[63] = "	gtk_main_quit();";
	code[64] = "}";
	code[65] = "";
	code[66] = "void show_photo_log( void )";
	code[67] = "{";
	code[68] = "	system( \"xdg-open /home/`whoami`/.alm/log/p_log\" );";
	code[69] = "}";
	
	
	
	for( i=0; i<70; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fclose(fd);
	printf("alm_interface.c created.\n");

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// alm_run.c
	
	fd = fopen( "alm_run.c", "w" );
		
	code[0] = "#include<stdio.h>";
	code[1] = "#include<stdlib.h>";
	code[2] = "";
	code[3] = "int compare( char *str1, char *str2)";
	code[4] = "{";
	code[5] = "	char *ptr1, *ptr2;";
	code[6] = "	for( ptr1=str1, ptr2=str2; (*(ptr1) != '\\0')	|| (*(ptr2) != '\\0');  ptr1++, ptr2++  )";
	code[7] = "	{";
	code[8] = "		if( *(ptr1) != *(ptr2) )";
	code[9] = "		{";
	code[10] = "			return 1;";
	code[11] = "		}";
	code[12] = "	}";
	code[13] = "	return 0;";
	code[14] = "}";
	code[15] = "";
	code[16] = "int main( int argc, char *argv[])";
	code[17] = "{";
	code[18] = "	if( argc < 2 )";
	code[19] = "	{";
	code[20] = "		return 0;";
	code[21] = "	}";
	code[22] = "	if( compare( argv[1], \"gui\") == 0 )";
	code[23] = "	{";
	code[24] = "		system( \"sleep 3 && /home/`whoami`/.alm/scripts/alm_gui\" );";
	code[25] = "		return 0;";
	code[26] = "	}";
	code[27] = "	else if( compare( argv[1], \"interface\") == 0 )";
	code[28] = "	{";
	code[29] = "		system( \"/home/`whoami`/.alm/scripts/alm_interface\" );";
	code[30] = "		return 0;";
	code[31] = "	}";
	code[32] = "	else if( compare( argv[1], \"cli\") == 0 )";
	code[33] = "	{";
	code[34] = "		system( \"/home/`whoami`/.alm/scripts/alm_cli\" );";
	code[35] = "		return 0;";
	code[36] = "	}";
	code[37] = "	return 0;";
	code[38] = "}";


	for( i=0; i<39; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fclose(fd);
	printf("alm_run.c created.\n");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// manage_files.sh
	
	fd = fopen( "manage_files.sh", "w" );

	code[0] = "#!/bin/bash";
	code[1] = "gcc -Wall -Wextra alm_gui_mode.c -o alm_gui `pkg-config --libs --cflags gtk+-2.0` > /dev/null 2>&1";
	code[2] = "gcc -Wall -Wextra alm_cli_mode.c -o alm_cli `pkg-config --libs --cflags gtk+-2.0` > /dev/null 2>&1";
	code[3] = "gcc -Wall -Wextra alm_interface.c -o alm_interface `pkg-config --libs --cflags gtk+-2.0` > /dev/null 2>&1";
	code[4] = "gcc -Wall -Wextra alm_run.c -o alm-run > /dev/null 2>&1";
	code[5] = "#rm alm_gui_mode.c alm_cli_mode.c alm_interface.c alm_run.c";
	code[6] = "if [ ! -f alm_gui ]";
	code[7] = "then";
	code[8] = "	echo 1";
	code[9] = "	exit 0";
	code[10] = "fi";
	code[11] = "mv alm_gui /home/`whoami`/.alm/scripts";
	code[12] = "mv alm_cli /home/`whoami`/.alm/scripts";
	code[13] = "mv alm_interface /home/`whoami`/.alm/scripts";
	code[14] = "mv alm.desktop /home/`whoami`/.config/autostart";
	code[15] = "file=$(grep  \"shopt -q login_shell &&  /bin/alm-run cli || : \" /home/`whoami`/.bashrc | wc -l)";
	code[16] = "if [ $file -eq 0 ]";
	code[17] = "then";
	code[18] = "	echo \"shopt -q login_shell &&  /bin/alm-run cli || : \" >> /home/`whoami`/.bashrc";
	code[19] = "fi";
	code[20] = "#gksu cp alm-run /bin";
	code[21] = "echo 0";
	code[22] = "#rm manage_files.sh";
	code[23] = "exit 0";
	
	for( i=0; i<24; i++ )
	{
		fprintf( fd, "\n%s", code[i] );
	}
	
	fclose(fd);
	printf("manage_files.sh created.\n");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}



void manage_files( void )
{
	int status;
	
	fd = popen( "sh manage_files.sh", "r" );
	fscanf( fd, "%d", &status );
	pclose(fd);
	
	
	if( status == 0 )
	{
		gtk_label_set_markup( GTK_LABEL( pattern_label ), "<span fgcolor=\"green\" font=\"11\">Installation completed.</span>" );
	}
	else
	{
		gtk_label_set_markup( GTK_LABEL( pattern_label ), "<span fgcolor=\"red\" font=\"11\">Error: gtk2 headers not found. retry again.</span>" );
	}
	gtk_widget_set_sensitive( GTK_WIDGET( cancel_button), TRUE );
}










