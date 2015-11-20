

//global variables

//opusway_intro
GtkWidget *main_window, *main_table;
GtkWidget *popup_window, *popup_entry;
GtkWidget *status_label, *install_button, *unlock_button, *body_frame, *cancel_button;

//setup1-5
GtkWidget *label[2], *entry[2], *next_button;;




GtkWidget *touch_button[25], *touch_label[25], *ok_button, *reset_button, *touch_table, *touch_frame, *window, *pattern_label;
char pattern[200], re_pattern[200], *target;
int count=0, old_lscount, new_lscount;



int install_status = 0;
char username[200], password[200], usb[100], final_pattern[200];


char system_user_name[50];

FILE *fd;





//functions used in project


// opusway_intro.c
void introduction_to_the_app( void );
void next_step( void );




//setup1&2-5.c
void installation_step_1( void );
void go_next( void );


//setup3-5.c
void usb_register( void );
int register_new_usb( void );


//setup4-5.c
void register_pattern( void );
void reset( void );
void change_color( GtkWidget *w, gpointer data );
void pattern_verify_and_save( void );


//setup5-5.c
void start_final_installation( void );
void create_directories( void );
void create_files( void );
void manage_files( void );


//extra.c
int compare( gchar *str1, char *str2);
int string_length( char *str);





