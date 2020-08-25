#include <gtk/gtk.h>

static void print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;
  cairo_surface_t *result;
  unsigned char *current_row;

  result = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 100, 100);

    cairo_surface_flush(result);
    current_row = cairo_image_surface_get_data(result);
    cairo_image_surface_get_stride(result);
    for (int y = 0; y < 100; y++) {
        uint32_t *row = (void *) current_row;
        for (int x = 0; x < 100; x++) {
            uint32_t r = 0xFF;
            uint32_t g = 0xFF;
            uint32_t b = 0x00;
            row[x] = (r << 16) | (g << 8) | b;
        }

        current_row += cairo_image_surface_get_stride(result);
    }
    cairo_surface_mark_dirty(result);

  /*context = gtk_widget_get_style_context (widget);

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  gtk_render_background (context, cr, 0, 0, width, height);

  cairo_arc (cr,
             width / 2.0, height / 2.0,
             MIN (width - 200, height) / 2.0,
             0, 0.5 * G_PI);

  gtk_style_context_get_color (context,
                               gtk_style_context_get_state (context),
                               &color);
  gdk_cairo_set_source_rgba (cr, &color);*/
 // cr = cairo_create(result);
    cairo_set_source_surface(cr, result, 0, 0);
  cairo_paint (cr);

 return FALSE;
}

static void activate (GtkApplication *app, gpointer user_data)
{
 GtkWidget *window;
 //GtkWidget *button;
// GtkWidget *button_box;
  GtkWidget *drawing_area = gtk_drawing_area_new ();

  //gtk_widget_set_size_request (drawing_area, 400, 400);


	window = gtk_application_window_new(app);

//gtk_window_set_title (GTK_WINDOW(app), "Window");
 	gtk_window_set_default_size (GTK_WINDOW(window), 600, 600);
	
  	gtk_widget_set_size_request (drawing_area, 400, 400);

  	g_signal_connect (G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), NULL);
  	gtk_container_add (GTK_CONTAINER (window), drawing_area);

  /*button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);*/

 gtk_widget_show_all (window);
}

int main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);


 // GtkWidget *drawing_area = gtk_drawing_area_new ();
  //gtk_widget_set_size_request (drawing_area, 100, 100);

  return status;
}
