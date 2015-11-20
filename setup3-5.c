


void usb_register( void )
{
	FILE *pd;
	
	gtk_frame_set_label( GTK_FRAME( body_frame), "Installation step - 3/5 (register a usb device)" );
	
	status_label = gtk_label_new("...");
	gtk_table_attach_defaults ( GTK_TABLE (main_table), status_label, 1, 11, 1, 9);
	gtk_widget_show( status_label );
	gtk_label_set_text( GTK_LABEL( status_label), "Insert the USB device. ( it will be used to unlock the system )\n\n\nIf the desired USB device is already inserted then simply remove it to register." );
	
	pd = popen( "lsusb | wc -l", "r" );
	system( "lsusb > old_data" );
	fscanf( pd, "%d", &old_lscount );
	pclose( pd );
	
	gtk_timeout_add( 1000, register_new_usb, NULL );
}






int register_new_usb( void )
{
	FILE *pd;
	
	pd = popen( "lsusb | wc -l", "r" );
	fscanf( pd, "%d", &new_lscount );
	pclose( pd );
	
	if( new_lscount == old_lscount )
	{
		return TRUE;
	}
	else
	{
		system( "lsusb > new_data" );
		pd = popen( "diff old_data new_data | tail -n 1 |  cut -b 26-34", "r" );
		fscanf( pd, "%s", usb );
		pclose(pd);
		
		system( "rm old_data new_data" );
		
		gtk_widget_destroy( status_label );
		register_pattern();
		return FALSE;
	}
}



