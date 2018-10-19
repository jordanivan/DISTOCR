#include <gtk/gtk.h>

static void open_dialog(gpointer window, GtkWidget *grid,GtkWidget *image,
			gchar *chemin)
{
	GtkWidget *dialog;
	
	dialog=gtk_file_chooser_dialog_new("Choose a file",GTK_WINDOW(window),
	GTK_FILE_CHOOSER_ACTION_OPEN,("_Cancel"),GTK_RESPONSE_OK,
	("_Choose"),GTK_RESPONSE_CANCEL,NULL);
		
	gtk_widget_show_all(dialog);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
	g_get_home_dir());
	gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
	if (resp==GTK_RESPONSE_OK)
		chemin=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	else
		g_print("You pressed the cancel\n");

	image=gtk_image_new_from_file(chemin);

	gtk_grid_attach(GTK_GRID(grid),image,0,1,3,1);

	gtk_widget_show_all(grid);

	gtk_widget_destroy(dialog);
}


int main(int argc,char* argv[])
{
	gtk_init(&argc,&argv);
      	//declare needed variable

  	GtkWidget *window,*button1,*button2,*button3, *grid;

	// create the window

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(window,"delete-event",
	
	// to quit window

	G_CALLBACK(gtk_main_quit),NULL);

        // our program start from here

	 // set grid's spacing 

	grid=gtk_grid_new();       
	gtk_grid_set_row_spacing(GTK_GRID(grid),10);
	gtk_grid_set_column_spacing(GTK_GRID(grid),10);
 	
	// set button parameter

	button1=gtk_button_new_with_mnemonic("Select Image");  
	button2=gtk_button_new_with_mnemonic("Display Text");
	button3=gtk_button_new_with_mnemonic("Train brain");
	
	
	 // set window name

	 //set button position in grid

	gtk_window_set_title(GTK_WINDOW(window),"DISTOCR"); 
        gtk_grid_attach(GTK_GRID(grid),button1,0,0,1,1);  
	gtk_grid_attach(GTK_GRID(grid),button2,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),button3,2,0,1,1);

	// to open_dialog function

	g_signal_connect(button1,"clicked",G_CALLBACK(open_dialog),
	(window, grid)); 
	
	//add grid to window

	gtk_container_add(GTK_CONTAINER(window),grid); 

	//set space to border's window

	gtk_container_set_border_width(GTK_CONTAINER(window),20); 
	gtk_widget_show_all(window);
	
	gtk_main();
	return EXIT_SUCCESS;

}
