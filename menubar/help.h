#ifndef HELP_H
#define HELP_H
#endif

#ifndef MAIN_H
#include "../main.h"
#endif

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview;
extern GtkCssProvider *css;

static void hello_world() {
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "<span size=\"36000\">Hello World!</span>");
    gtk_widget_set_name(dialog, "dialog");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void about_dialog() {
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "<span size=\"36000\">txtedit</span>\n<span size=\"18000\">another very bad program (after mspaint 2) written in gtk3</span>");
    gtk_widget_set_name(dialog, "dialog");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void help_menu_init() {
    GtkWidget *help_label, *help_menu, *about, *hwrld;

    help_label = gtk_menu_item_new_with_mnemonic("_Help");
    help_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_label), help_menu);

    about = gtk_menu_item_new_with_label("About");
    g_signal_connect(about, "activate", G_CALLBACK(about_dialog), NULL);

    hwrld = gtk_menu_item_new_with_label("Hello world");
    g_signal_connect(hwrld, "activate", G_CALLBACK(hello_world), NULL);

    gtk_menu_attach(GTK_MENU(help_menu), about, 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(help_menu), hwrld, 0, 1, 1, 2);

    gtk_widget_set_name(help_menu, "help");

    gtk_container_add(GTK_CONTAINER(menubar), help_label);
}