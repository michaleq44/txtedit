#include <main.h>

int main(int argc, char** argv) {
    app = gtk_application_new("io.github.michaleq44.txtedit", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}