#include<stdio.h>
#include<stdlib.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

 
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "DISTOCR");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_container_set_border_width (GTK_CONTAINER(window), 10);

  grid = gtk_grid_new ();

  gtk_container_add(GTK_CONTAINER(window), grid);
  /* creation des boutons*/
  
                                                  
  gtk_grid_attach(GTK_GRID(grid),button,0,0,1,1);
  
  button = gtk_button_new_with_label("Process");
 
  gtk_grid_attach(GTK_GRID(grid),button,0,3,1,1);

  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button,"cliked",G_CALLBACK(gtk_widget_destroy),window);
  gtk_grid_attach(GTK_GRID(grid),button,0,5,1,1);


  gtk_widget_show(window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
