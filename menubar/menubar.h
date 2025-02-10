#ifndef MENUBAR_H
#define MENUBAR_H
#endif

#ifndef MAIN_H
#include "../main.h"
#endif

#ifndef FILE_H
#include "file.h"
#endif

#ifndef HELP_H
#include "help.h"
#endif

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview;
extern GtkCssProvider *css;

static void menubar_init() {
    menubar = gtk_menu_bar_new();
    gtk_widget_set_name(menubar, "menubar");
    gtk_widget_set_size_request(menubar, 200, 16);
    gtk_widget_set_vexpand(menubar, FALSE);
    gtk_widget_set_hexpand(menubar, TRUE);
    gtk_menu_bar_set_child_pack_direction(GTK_MENU_BAR(menubar), GTK_PACK_DIRECTION_LTR);

    file_menu_init();
    help_menu_init();

    gtk_grid_attach(GTK_GRID(grid), menubar, 0, 0, 1, 1);
}