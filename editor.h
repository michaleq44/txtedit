#ifndef EDITOR_H
#define EDITOR_H
#endif

#ifndef MAIN_H
#include "main.h"
#endif

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview, *scrlwin;
extern GtkCssProvider *css;

static void txt_init() {
    scrlwin = gtk_scrolled_window_new(NULL, NULL);
    txtview = gtk_text_view_new();

    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(txtview), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(txtview), 10);
    gtk_container_add(GTK_CONTAINER(scrlwin), txtview);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrlwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_hexpand(scrlwin, TRUE);
    gtk_widget_set_vexpand(scrlwin, TRUE);
    gtk_widget_set_name(scrlwin, "txtview");
    gtk_grid_attach(GTK_GRID(grid), scrlwin, 0, 1, 1, 1);
}