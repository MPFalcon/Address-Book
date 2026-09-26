#include "main.h"

int main(int argc, char ** argv)
{
    int              exit_code = EXIT_FAILURE;
    int              status    = FAILURE;
    GtkApplication * app       = NULL;

    DEBUGPRINTF("%s", "Starting address book GUI...");

#ifdef GTK_SRCDIR
    g_chdir(GTK_SRCDIR);
#endif

    // Create a new GTK application
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    exit_code = EXIT_SUCCESS;

    return exit_code;
}

// EOF
