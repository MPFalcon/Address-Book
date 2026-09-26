#ifndef MODEL_H
#    define MODEL_H

#    include <gtk/gtk.h>
#    include "common.h"

/**
 * @brief Activate the application.
 *
 * @param app The GTK application.
 * @param user_data User data passed to the callback (unused).
 */
void activate(GtkApplication * app, gpointer user_data);

#endif /* MODEL_H */

// EOF
