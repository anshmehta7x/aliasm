#include "export.h"
#include <iostream>

ExportWindow::ExportWindow(std::vector<std::pair<std::string, std::string>> aliases)
{

  this->aliases = aliases;
  set_title("Select Export Destination");
  auto dialog = Gtk::FileDialog::create();
  dialog->select_folder(sigc::bind(sigc::mem_fun(*this,
                &ExportWindow::on_folder_dialog_finish), dialog));
}

ExportWindow::~ExportWindow()
{
}

void ExportWindow::on_folder_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gtk::FileDialog>& dialog)
{
  try
  {
    auto folder = dialog->select_folder_finish(result);
    std::cout << "Folder selected: " << folder->get_path() << std::endl;
    directory = folder->get_path();
    write_file();
  }
  catch (const Gtk::DialogError& err)
  {
    std::cout << "No folder selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
  this->hide();

}


bool ExportWindow::write_file()
{
    fileManager.writeAliasesToFile(directory,aliases);

    return true;
}
