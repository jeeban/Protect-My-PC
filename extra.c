int string_length( char *str)
{
	int i;
	char *ptr;
	for( i=0, ptr=str ; *(ptr) != '\0' ; i++, ptr++){}
	
	return i;
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

