#include "model.h"
#include <glib/gstdio.h>

/**
 * @brief Callback function to print "Hello World" when a button is clicked.
 *
 * @param widget The widget that triggered the callback.
 * @param data User data passed to the callback (unused).
 */
static void print_hello(GtkWidget * widget, gpointer data)
{
    g_print("Hello World\n");
}

/**
 * @brief Callback function to quit the application when the quit button is
 * clicked.
 *
 * @param window The GTK window to close.
 */
static void quit_cb(GtkWindow * window)
{
    gtk_window_close(window);
}

void activate(GtkApplication * app, gpointer user_data)
{
    /* Construct a GtkBuilder instance and load our UI description */
    GtkBuilder * builder = gtk_builder_new();
#ifdef BUILDER_UI_PATH
    gtk_builder_add_from_file(builder, BUILDER_UI_PATH, NULL);
#else
    gtk_builder_add_from_file(builder, "builder.ui", NULL);
#endif

    /* Connect signal handlers to the constructed widgets. */
    GObject * window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW(window), app);

    GObject * button = gtk_builder_get_object(builder, "button1");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    button = gtk_builder_get_object(builder, "button2");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_cb), window);

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);

    /* We do not need the builder any more */
    g_object_unref(builder);
}

// EOF
