#ifndef MAIN_H
#define MAIN_H
#endif

#include <gtk/gtk.h>

#ifndef MENUBAR_H
#include "menubar/menubar.h"
#endif

#ifndef EDITOR_H
#include "editor.h"
#endif

int status;
GtkApplication *app;
GtkWidget *window, *grid, *menubar, *txtview, *scrlwin;
GtkCssProvider *css;
char* savefile = "unnamed.txt";
gboolean saved = FALSE;
char *last = "";

static void activate(GtkApplication *app, gpointer user_data) {
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "txtedit (worse than mspaint2)");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "delete-event", G_CALLBACK(quit_prog), NULL);

    css = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css, "../data/style.css", NULL);

    GdkScreen *screen = gtk_widget_get_screen(window);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_set_name(window, "appwin");

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    menubar_init();
    txt_init();

    gtk_widget_show_all(window);
}