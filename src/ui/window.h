#ifndef ALIASM_UI_WINDOW_H
#define ALIASM_UI_WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/stringlist.h>
#include <gtkmm/box.h>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../util/file.h"

class MainWindow : public Gtk::Window {
public:
    Gtk::Box m_box;
    Gtk::DropDown dropdown;
    Gtk::Label statusLabel;

    filemanager fileManager;
    std::pair<Glib::ustring, std::string> selectedItem; // stores shell , filename
    std::vector<std::pair<std::string, std::string>> aliases;

    MainWindow(std::vector<Glib::ustring> items) :
        m_box(Gtk::Orientation::VERTICAL, 10) // Vertical box with 10px spacing
    {
        set_title("Alias Manager");
        set_default_size(300, 200);
        set_resizable(true);
        set_child(m_box);
        statusLabel.set_margin(10);

        if(items.size() == 0) {
            statusLabel.set_text(".bashrc or .zshrc not found");
            m_box.append(statusLabel);
        } else {
            setupDropdown(items);
            m_box.append(dropdown);

            statusLabel.set_text("Select a shell");
            m_box.append(statusLabel);
        }

        dropdown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_change)
        );
    }

    void on_dropdown_change() {
        guint index = dropdown.get_selected();
        if (index == GTK_INVALID_LIST_POSITION)
            return;

        auto model = dropdown.get_model();
        auto string_list = std::dynamic_pointer_cast<Gtk::StringList>(model);
        if (!string_list) return;

        Glib::ustring shell = string_list->get_string(index);
        selectedItem = std::make_pair(shell, getFilename(shell));
        std::cout << selectedItem.first << " " << selectedItem.second << std::endl;
        aliases = fileManager.getAliases(selectedItem.second);

        if(aliases.size() == 0) {
            statusLabel.set_text("No aliases found");
        } else {
            statusLabel.set_text("Found " + std::to_string(aliases.size()) + " aliases");
        }
    }

    std::string getFilename(Glib::ustring shell) {
        if(shell == "zsh") {
            return ".zshrc";
        }
        else if(shell == "bash") {
            return ".bashrc";
        }
        else {
            throw std::runtime_error("Unknown shell type");
        }
    }

    void setupDropdown(std::vector<Glib::ustring> items) {
        dropdown = Gtk::DropDown(items);
        dropdown.set_margin(10);
        dropdown.set_selected(0);
        selectedItem = std::make_pair(items[0], getFilename(items[0]));
    }

    virtual ~MainWindow() {}
};

#endif // ALIASM_UI_WINDOW_H
