#include "importwindow.h"
#include <iostream>

ImportWindow::ImportWindow(const std::function<void(const std::vector<std::pair<std::string, std::string>>&)>& callback)
    : importCallback(callback) {
    set_title("Select File to Import");

    auto dialog = Gtk::FileDialog::create();
    dialog->open(sigc::bind(sigc::mem_fun(*this, &ImportWindow::on_file_dialog_finish), dialog));
}

ImportWindow::~ImportWindow() {}

void ImportWindow::on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
                                        const Glib::RefPtr<Gtk::FileDialog>& dialog) {
    try {
        auto file = dialog->open_finish(result);
        std::string filepath = file->get_path();
        std::cout << "File selected: " << filepath << std::endl;

        auto aliases = fileManager.readAliasesFromFile(filepath);
        if (!aliases.empty()) {
            importCallback(aliases);
        }
    } catch (const Gtk::DialogError& err) {
        std::cout << "No file selected. " << err.what() << std::endl;
    } catch (const Glib::Error& err) {
        std::cout << "Unexpected exception. " << err.what() << std::endl;
    }

    this->hide();
}
