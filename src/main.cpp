#include <gtkmm/application.h>
#include "ui/mainwindow.h"
// #include "ui/rc_picker.h"
#include <vector>
#include "util/file.h"


int main(int argc, char* argv[]) {
    filemanager f;
    std::vector<Glib::ustring> items;
    if (f.searchRc(".zshrc")){
        items.push_back("zsh");
    }
    if (f.searchRc(".bashrc")){
        items.push_back("bash");
    }

    auto app = Gtk::Application::create("aliasm");
    app->signal_activate().connect([&items, app]() {
        auto window = new MainWindow(items);
        app->add_window(*window);
        window->show();
    });

    return app->run(argc, argv);
}
