#ifndef ALIASM_UI_WINDOW_H
#define ALIASM_UI_WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/stringlist.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <glibmm/main.h>
#include <utility>
#include <vector>
#include <string>
#include <functional>
#include "../util/file.h"
#include "aliaslist.h"
#include "featurerow.h"

class MainWindow : public Gtk::Window {
public:
    MainWindow(std::vector<Glib::ustring> items);

private:
    Gtk::Box m_box;
    Gtk::DropDown dropdown;
    Gtk::Label statusLabel;
    AliasList aliasList;
    Gtk::ScrolledWindow scrolled;
    FeatureButtonRow add;

    filemanager fileManager;
    std::pair<Glib::ustring, std::string> selectedItem;
    std::vector<std::pair<std::string, std::string>> aliases;

    std::function<void()> addClicked;
    std::function<void()> exportClicked;
    std::function<void()> importClicked;

    void update_status_label(std::string newText);
    void on_dropdown_change();
    void saveAlias(const std::string& oldAlias, const std::string& newAlias, const std::string& command);
    void removeAlias(const std::string& alias);
    void refreshAliasList();
    std::string getFilename(Glib::ustring shell);
    void setupDropdown(std::vector<Glib::ustring> items);
};

#endif
