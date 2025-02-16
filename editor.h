#ifndef EDITOR_H
#define EDITOR_H
#endif

#ifndef MAIN_H
#include "main.h"
#endif

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview, *scrlwin, *lineview;
extern GtkCssProvider *css;
extern GtkTextBuffer *buf;
gchar *text;
GValue val;
gboolean ctrl, alt;

static void key_callback(GtkWidget *w, GdkEventKey *event, gpointer user_data) {
    guint n_lines;
    GtkTextBuffer *buffer;
    text = malloc(1000000);
    strcpy(text, "");
    gtk_widget_grab_focus(txtview);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
    n_lines = gtk_text_buffer_get_line_count(buffer);

    for (int i = 1; i <= n_lines+1; i++) {
        strcat(text, g_strdup_printf("%d\n", i));
    }
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(lineview));
    gtk_text_buffer_set_text(buffer, text, strlen(text));
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
            default:;
        }
    }
    if (event->state == GDK_CONTROL_MASK | GDK_SHIFT_MASK) {
        switch (event->keyval) {
            case GDK_KEY_S:
                saveas_file();
                break;
            default:;
        }
    }
}

static void btn_callback(GtkWidget *w, GdkEventButton *event) {
#ifdef DEBUG
    g_print("button press: %d\n", event->button);
#endif
    gtk_widget_grab_focus(txtview);
}

static void txt_init() {
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *viewport = gtk_viewport_new(NULL, NULL);
    scrlwin = gtk_scrolled_window_new(NULL, NULL);
    txtview = gtk_text_view_new();
    g_value_init(&val, G_TYPE_STRING);
    g_value_set_string(&val, "Sans Serif");
    GtkTextTag *tag = gtk_text_tag_new("cline");
    GtkTextTagTable *tagtabl = gtk_text_tag_table_new();
    gtk_text_tag_table_add(tagtabl, tag);
    g_object_set_property(G_OBJECT(tag), "font", &val);
    buf = gtk_text_buffer_new(tagtabl);
    lineview = gtk_text_view_new_with_buffer(buf);

    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(txtview), 2);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(txtview), 10);
    gtk_widget_add_events(txtview, GDK_KEY_PRESS);
    g_signal_connect(txtview, "key-press-event", G_CALLBACK(key_callback), NULL);
    g_signal_connect(txtview, "button-press-event", G_CALLBACK(btn_callback), NULL);
    g_signal_connect(txtview, "button-release-event", G_CALLBACK(btn_callback), NULL);
    gtk_widget_set_can_focus(txtview, TRUE);
    /*gtk_widget_set_vexpand(lineview, TRUE);
    gtk_widget_set_hexpand(lineview, FALSE);
    gtk_widget_set_size_request(lineview, 16, 200);*/
    gtk_widget_set_hexpand(txtview, TRUE);
    gtk_widget_set_vexpand(txtview, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(lineview), FALSE);

    //gtk_box_pack_start(GTK_BOX(hbox), lineview, FALSE, FALSE, 0);
    //gtk_box_pack_start(GTK_BOX(hbox), txtview, TRUE, TRUE, 0);

    //gtk_container_add(GTK_CONTAINER(viewport), hbox);
    gtk_container_add(GTK_CONTAINER(scrlwin), txtview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrlwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_hexpand(scrlwin, TRUE);
    gtk_widget_set_vexpand(scrlwin, TRUE);
    gtk_widget_set_name(scrlwin, "txtview");
    gtk_grid_attach(GTK_GRID(grid), scrlwin, 0, 1, 1, 1);
    gtk_widget_grab_focus(txtview);
}