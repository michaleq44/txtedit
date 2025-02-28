#ifndef EDITOR_H
#define EDITOR_H
#endif

#ifndef MAIN_H
#include <main.h>
#endif

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview, *scrlwin;
extern GtkCssProvider *css;
extern GtkTextBuffer *buf;
gchar *text;

static void key_callback(GtkWidget *w, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_F1) about_dialog();

    if (event->state == GDK_CONTROL_MASK) {
        switch (event->keyval) {
            case GDK_KEY_n:
                new_file();
            break;
            case GDK_KEY_o:
                open_file();
            break;
            case GDK_KEY_s:
                save_file();
            break;
            case GDK_KEY_q:
                quit_prog();
            break;
            case GDK_KEY_h:
                hello_world();
            default:;
        }
    }
    if (event->state == GDK_CONTROL_MASK + GDK_SHIFT_MASK) {
        switch (event->keyval) {
            case GDK_KEY_S:
                saveas_file();
            break;
            default:;
        }
    }

#ifdef DEBUG
    g_print("key press: %s | mod: %d\n", gdk_keyval_name(event->keyval), event->state);
#endif
}

static void btn_callback(GtkWidget *w, GdkEventButton *event) {
#ifdef DEBUG
    g_print("button press: %d\n", event->button);
#endif
    gtk_widget_grab_focus(txtview);
}

static void nulla() {};

static void txt_init() {
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);


    scrlwin = gtk_scrolled_window_new(NULL, NULL);
    txtview = gtk_text_view_new();


    GtkTextTagTable *tagtabl = gtk_text_tag_table_new();
    buf = gtk_text_buffer_new(tagtabl);

    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(txtview), 2);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(txtview), 10);
    gtk_widget_add_events(txtview, GDK_KEY_PRESS);
    g_signal_connect(window, "key-press-event", G_CALLBACK(key_callback), NULL);
    g_signal_connect(txtview, "button-press-event", G_CALLBACK(btn_callback), NULL);
    g_signal_connect(txtview, "button-release-event", G_CALLBACK(btn_callback), NULL);

    gtk_widget_set_can_focus(txtview, TRUE);
    gtk_widget_set_hexpand(txtview, TRUE);
    gtk_widget_set_vexpand(txtview, TRUE);

    gtk_container_add(GTK_CONTAINER(scrlwin), txtview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrlwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_box_pack_start(GTK_BOX(hbox), scrlwin, TRUE, TRUE, 2);

    gtk_widget_set_hexpand(scrlwin, TRUE);
    gtk_widget_set_vexpand(scrlwin, TRUE);
    gtk_widget_set_name(txtview, "txtview");
    gtk_grid_attach(GTK_GRID(grid), hbox, 0, 1, 1, 1);
    gtk_widget_grab_focus(txtview);
}