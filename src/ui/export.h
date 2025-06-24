#ifndef EXPORT_WINDOW_H
#define EXPORT_WINDOW_H

#include <gtkmm.h>
#include "file.h"


class ExportWindow : public Gtk::Window
{
public:
  ExportWindow(std::vector<std::pair<std::string, std::string>> aliases);
  ~ExportWindow() override;

protected:
  void on_folder_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
                               const Glib::RefPtr<Gtk::FileDialog>& dialog);


private:
    std::vector<std::pair<std::string, std::string>> aliases;
    std::string directory = "";
    bool write_file();
    filemanager fileManager;
};
#endif // EXPORT_WINDOW_H
