#ifndef FILE_H
#define FILE_H
#endif

#ifndef MAIN_H
#include <main.h>
#endif

extern int status;
extern GtkApplication *app;
extern GtkWidget *window, *grid, *menubar, *txtview;
extern GtkCssProvider *css;
extern char* savefile;
extern gboolean saved;
extern char *last;

static GtkWidget *menu_item_new_with_keyboard(const char* desc, const gchar* shortcut) {
    GtkWidget *menu_item = gtk_menu_item_new();
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *dlabel, *klabel;
    dlabel = gtk_label_new(desc);
    char *format = malloc(1000);
    strcpy(format, "<span color=\"#999999\" gravity=\"west\">");
    strcat(format, shortcut);
    strcat(format, "</span>");
    klabel = gtk_label_new(format);
    gtk_label_set_use_markup(GTK_LABEL(klabel), TRUE);
    gtk_label_set_xalign(GTK_LABEL(klabel), 1.0f);
    gtk_label_set_xalign(GTK_LABEL(dlabel), 0.0f);

    gtk_label_set_single_line_mode(GTK_LABEL(dlabel), TRUE);
    gtk_label_set_single_line_mode(GTK_LABEL(klabel), TRUE);

    gtk_box_pack_start(GTK_BOX(hbox), dlabel, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(hbox), klabel, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(menu_item), hbox);

    return menu_item;
}

static gboolean streq(gchar* s1, gchar* s2) {
    if (strlen(s1) != strlen(s2)) return FALSE;
    for (int i = 0; i < strlen(s1); i++) if (s1[i] != s2[i]) return FALSE;
    return TRUE;
}

static void quit_prog() {
    char *txt;
    GtkTextBuffer *buf;
    GtkTextIter siter, eiter;
    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
    gtk_text_buffer_get_start_iter(buf, &siter);
    gtk_text_buffer_get_end_iter(buf, &eiter);
    txt = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);

    gint res = GTK_RESPONSE_OK;

    gboolean eq = TRUE;
    for (int i = 0; i < gtk_text_buffer_get_char_count(buf); i++) {
        if (last[i] != txt[i]) eq = FALSE;
    }

    if (!eq) {
        GtkWidget *dialog;

        dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_OK, "<span size=\"18000\">You might have unsaved changes. Are you sure you want to quit?</span>", NULL);
        res = gtk_dialog_run(GTK_DIALOG(dialog));
    }
    g_free(txt);

    if (res == GTK_RESPONSE_OK) g_application_quit(G_APPLICATION(app));
}

static void open_file() {
    char *txt1;
    gsize nlen;
    GtkTextBuffer *buf;
    GtkTextIter siter, eiter;
    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
    gtk_text_buffer_get_start_iter(buf, &siter);
    gtk_text_buffer_get_end_iter(buf, &eiter);
    txt1 = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);

    gint res1 = GTK_RESPONSE_OK;
    gboolean eq = TRUE;
    for (int i = 0; i < gtk_text_buffer_get_char_count(buf); i++) {
        if (last[i] != txt1[i]) eq = FALSE;
    }

    if (!eq) {
        GtkWidget *dialog1;
        dialog1 = gtk_message_dialog_new_with_markup(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_OK, "<span size=\"18000\">You might have unsaved changes. Are you sure you want to open new file?</span>", NULL);
        res1 = gtk_dialog_run(GTK_DIALOG(dialog1));
    }
    g_free(txt1);

    if (res1 != GTK_RESPONSE_OK) return;

    GtkWidget *dialog;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        savefile = gtk_file_chooser_get_filename(chooser);

        g_file_get_contents(savefile, &last, &nlen, NULL);
        g_print("%d\n", nlen);
        gtk_text_buffer_set_text(buf, "", 0);
        gtk_text_buffer_get_start_iter(buf, &siter);
        gtk_text_buffer_get_end_iter(buf, &eiter);
        //g_print("%s", gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE));
        saved = TRUE;

    }
    gtk_text_buffer_insert(buf, &siter, last, nlen);

    gtk_widget_destroy(dialog);
}

static void saveas_file() {
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
    chooser = GTK_FILE_CHOOSER(dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
    if (saved) gtk_file_chooser_set_current_name(chooser, "unnamed.txt");
    else gtk_file_chooser_set_filename(chooser, savefile);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *txt;
        GtkTextBuffer *buf;
        GtkTextIter siter, eiter;
        savefile = gtk_file_chooser_get_filename(chooser);
        buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
        gtk_text_buffer_get_start_iter(buf, &siter);
        gtk_text_buffer_get_end_iter(buf, &eiter);
        txt = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);
        last = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);

        g_file_set_contents(savefile, txt, gtk_text_buffer_get_char_count(buf), NULL);
        saved = TRUE;
        g_free(txt);
    }

    gtk_widget_destroy(dialog);
}

static void save_file() {
    if (saved) {
        char *txt;
        GtkTextBuffer *buf;
        GtkTextIter siter, eiter;
        buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
        gtk_text_buffer_get_start_iter(buf, &siter);
        gtk_text_buffer_get_end_iter(buf, &eiter);
        txt = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);
        last = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);

        g_file_set_contents(savefile, txt, gtk_text_buffer_get_char_count(buf), NULL);
        saved = TRUE;
        g_free(txt);
        g_free(savefile);
    } else saveas_file();
}

static void new_file() {
    char *txt;
    GtkTextBuffer *buf;
    GtkTextIter siter, eiter;
    buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
    gtk_text_buffer_get_start_iter(buf, &siter);
    gtk_text_buffer_get_end_iter(buf, &eiter);
    txt = gtk_text_buffer_get_text(buf, &siter, &eiter, FALSE);

    gint res = GTK_RESPONSE_OK;

    gboolean eq = TRUE;
    for (int i = 0; i < gtk_text_buffer_get_char_count(buf); i++) {
        if (last[i] != txt[i]) eq = FALSE;
    }

    if (!eq) {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_OK, "<span size=\"18000\">You might have unsaved changes. Are you sure you want to erase file?</span>", NULL);
        res = gtk_dialog_run(GTK_DIALOG(dialog));
    }

    if (res == GTK_RESPONSE_OK) {
        GtkTextBuffer *buffer;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtview));
        gtk_text_buffer_set_text(buffer, "", 0);
        savefile = "unnamed.txt";
        saved = FALSE;
    }
}

static void file_menu_init() {
    GtkWidget *file_label, *file_menu, *quit, *open, *saveas, *save, *neew;

    file_label = gtk_menu_item_new_with_mnemonic("_File");
    file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_label), file_menu);

    save = menu_item_new_with_keyboard("Save", "Ctrl+S");
    g_signal_connect(save, "activate", G_CALLBACK(save_file), NULL);

    saveas = menu_item_new_with_keyboard("Save As...", "Ctrl+Shift+S");
    g_signal_connect(saveas, "activate", G_CALLBACK(saveas_file), NULL);

    open = menu_item_new_with_keyboard("Open...", "Ctrl+O");
    g_signal_connect(open, "activate", G_CALLBACK(open_file), NULL);

    quit = menu_item_new_with_keyboard("Quit", "Ctrl+Q");
    g_signal_connect(quit, "activate", G_CALLBACK(quit_prog), NULL);

    neew = menu_item_new_with_keyboard("New", "Ctrl+N");
    g_signal_connect(neew, "activate", G_CALLBACK(new_file), NULL);

    gtk_menu_attach(GTK_MENU(file_menu), neew, 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(file_menu), open, 0, 1, 1, 2);
    gtk_menu_attach(GTK_MENU(file_menu), save, 0, 1, 2, 3);
    gtk_menu_attach(GTK_MENU(file_menu), saveas, 0, 1, 3, 4);
    gtk_menu_attach(GTK_MENU(file_menu), quit, 0, 1, 4, 5);

    gtk_widget_set_name(file_menu, "file");

    gtk_container_add(GTK_CONTAINER(menubar), file_label);
}