#ifndef ALIASM_UI_IMPORTWINDOW_H
#define ALIASM_UI_IMPORTWINDOW_H

#include <gtkmm.h>
#include "../util/file.h"

class ImportWindow : public Gtk::Window {
public:
    ImportWindow(const std::function<void(const std::vector<std::pair<std::string, std::string>>&)>& callback);
    ~ImportWindow() override;

protected:
    void on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
                              const Glib::RefPtr<Gtk::FileDialog>& dialog);

private:
    std::function<void(const std::vector<std::pair<std::string, std::string>>&)> importCallback;
    filemanager fileManager;
};

#endif
