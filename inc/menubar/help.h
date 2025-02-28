#ifndef HELP_H
#define HELP_H
#endif

#ifndef UNICODE
#define UNICODE
#endif

#ifndef MAIN_H
#include <main.h>
#endif

#ifndef FILE_H
#include <file.h>
#endif

#include <windows.h>

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview;
extern GtkCssProvider *css;

HGDIOBJ gdk_win32_window_get_handle(GdkWindow *window);

//GtkWidget *menu_item_new_with_keyboard(const char* desc, const gchar* shortcut);

static void hello_world() {
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "<span size=\"36000\">Hello World!</span>");
    gtk_widget_set_name(dialog, "dialog");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

gulong abtinst;

static void k(GtkWidget *w, const GdkEventButton *event, gulong inst, gpointer user_data) {
    if (event->button != 2) return;
    char *txt;
    GtkTextBuffer *buf;
    GtkTextIter siter, eiter;
    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
    gtk_text_buffer_get_start_iter(buf, &siter);
    gtk_text_buffer_get_end_iter(buf, &eiter);
    txt = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);

    if (!streq(txt, "#include <windows.h>")) return;

#ifdef DEBUG
    g_print("EASTER EGG!!!\n");
#endif

    GtkWidget *lbl = g_list_nth_data(gtk_container_get_children(GTK_CONTAINER(w)), 0);
    gtk_label_set_markup(GTK_LABEL(lbl), "<span size=\"36000\">win32 api\n</span><span size=\"18000\">Ta pisanka była napisana w czystym...\nwin32 interfejsie programowania aplikacji. pomocy\n</span>");
    g_signal_handler_disconnect(w, inst);

    const HWND hwnd = gdk_win32_window_get_handle(gtk_widget_get_window(gtk_widget_get_parent(gtk_widget_get_parent(w))));
    MessageBox(hwnd, L"GRATULACJE UŻYTKOWNIKU!\nZnalazłeś pisankę!", L"Easter Egg", MB_OK);
}

static void kill_dialog(GtkWidget *w, gpointer user_data) {
    gtk_widget_destroy(gtk_widget_get_parent(gtk_widget_get_parent(w)));
}

static void about_dialog() {
    GtkWidget *dialog, *label, *vbox, *btn, *ebox;

    dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(dialog), TRUE);
    label = gtk_label_new("txtedit");
    gtk_label_set_markup(GTK_LABEL(label), "<span size=\"36000\">txtedit</span>\n<span size=\"18000\">another very bad program (after mspaint 2)\nwritten in gtk3\n</span>");
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_widget_set_size_request(dialog, 620, 200);

    btn = gtk_button_new_with_label("OK");
    g_signal_connect(btn, "clicked", G_CALLBACK(kill_dialog), NULL);

    ebox = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(ebox), label);

    abtinst = g_signal_connect(ebox, "button-press-event", G_CALLBACK(k), &abtinst);

    gtk_box_pack_start(GTK_BOX(vbox), ebox, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(vbox), btn, FALSE, FALSE, 0);

    gtk_window_set_title(GTK_WINDOW(dialog), "");
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), "../data/icon.png", NULL);
    gtk_window_set_type_hint(GTK_WINDOW(dialog), GDK_WINDOW_TYPE_HINT_DIALOG);

    gtk_container_add(GTK_CONTAINER(dialog), vbox);
    gtk_widget_set_name(dialog, "dialog");

    gtk_widget_show_all(dialog);
}

static void help_menu_init() {
    GtkWidget *help_label, *help_menu, *about, *hwrld;

    help_label = gtk_menu_item_new_with_mnemonic("_Help");
    help_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_label), help_menu);

    about = menu_item_new_with_keyboard("About", "F1");
    g_signal_connect(about, "activate", G_CALLBACK(about_dialog), NULL);

    hwrld = menu_item_new_with_keyboard("Hello world", "Ctrl+H");
    g_signal_connect(hwrld, "activate", G_CALLBACK(hello_world), NULL);

    gtk_menu_attach(GTK_MENU(help_menu), about, 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(help_menu), hwrld, 0, 1, 1, 2);

    gtk_widget_set_name(help_menu, "help");

    gtk_container_add(GTK_CONTAINER(menubar), help_label);
}