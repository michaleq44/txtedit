#ifndef FILE_H
#define FILE_H
#endif

#ifndef MAIN_H
#include "../main.h"
#endif

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview;
extern GtkCssProvider *css;

static void quit_prog() {
    g_application_quit(G_APPLICATION(app));
}

static void open_file() {
    GtkWidget *dialog;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename, *txt;
        gsize nlen;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        g_file_get_contents(filename, &txt, &nlen, NULL);

        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
        gtk_text_buffer_set_text(buffer, txt, nlen);

        g_free(txt);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

static void file_menu_init() {
    GtkWidget *file_label, *file_menu, *quit, *open;
    int y = 0;

    file_label = gtk_menu_item_new_with_mnemonic("_File");
    file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_label), file_menu);

    quit = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(quit, "activate", G_CALLBACK(quit_prog), NULL);

    open = gtk_menu_item_new_with_label("Open");
    g_signal_connect(open, "activate", G_CALLBACK(open_file), NULL);

    gtk_menu_attach(GTK_MENU(file_menu), open, 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(file_menu), quit, 0, 1, 1, 2);

    gtk_widget_set_name(file_menu, "file");

    gtk_container_add(GTK_CONTAINER(menubar), file_label);
}