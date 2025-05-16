#ifndef ALIASM_UI_WINDOW_H
#define ALIASM_UI_WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/stringlist.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../util/file.h"
#include "aliaslist.h"
#include "addalias.h"
#include <glibmm/main.h>
#include "newaliaswindow.h"
#include "confirm.h"

class MainWindow : public Gtk::Window {
public:
    Gtk::Box m_box;
    Gtk::DropDown dropdown;
    Gtk::Label statusLabel;
    AliasList aliasList;
    Gtk::ScrolledWindow scrolled;
    AddButton add;

    filemanager fileManager;
    std::pair<Glib::ustring, std::string> selectedItem;
    std::vector<std::pair<std::string, std::string>> aliases;

    MainWindow(std::vector<Glib::ustring> items) :
        m_box(Gtk::Orientation::VERTICAL, 10)
    {
        set_title("Alias Manager");
        set_default_size(500, 400);
        set_resizable(true);
        set_child(m_box);

        statusLabel.set_margin(10);
        scrolled.set_child(aliasList);
        scrolled.set_vexpand(true);
        scrolled.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);

        if(items.size() == 0) {
            update_status_label(".bashrc or .zshrc not found");
            m_box.append(statusLabel);
        } else {
            setupDropdown(items);
            m_box.append(dropdown);
            statusLabel.set_visible(false);
            add.set_on_click(addClicked);
            m_box.append(statusLabel);
            m_box.append(add);
            m_box.append(scrolled);
            on_dropdown_change();
        }

        dropdown.property_selected().signal_changed().connect(
            sigc::mem_fun(*this, &MainWindow::on_dropdown_change)
        );
    }

    void update_status_label(std::string newText){
        statusLabel.set_visible(true);
        statusLabel.set_text(newText);
        Glib::signal_timeout().connect_once([&](){
            statusLabel.set_visible(false);
        }, 2000);
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

        aliasList.removeAliases();

        if(aliases.size() == 0) {
            update_status_label("No aliases found");
        } else {
            update_status_label(std::to_string(aliases.size()) + " aliases found");
            aliasList.addAliases(
                aliases,
                [this](const std::string& oldAlias, const std::string& newAlias, const std::string& command) {
                    saveAlias(oldAlias, newAlias, command);
                },
                [this](const std::string& alias) {
                    removeAlias(alias);
                }
            );
        }
    }


    void saveAlias(const std::string& oldAlias, const std::string& newAlias, const std::string& command) {
        std::cout << "Saving: " << oldAlias << " → " << newAlias << " = " << command << std::endl;

        if (fileManager.updateAlias(selectedItem.second, oldAlias, newAlias, command)) {
            update_status_label("Alias updated successfully");
        } else {
            update_status_label("Failed to update alias");
        }
        refreshAliasList();
    }

    void removeAlias(const std::string& alias) {
        std::cout << "Removing alias: " << alias << std::endl;

        auto confirmWindow = new ConfirmWindow(
            "Are you sure you want to remove this alias?",
            [this, alias]() {
                if (fileManager.removeAlias(selectedItem.second, alias)) {
                    update_status_label("Alias removed successfully");
                } else {
                    update_status_label("Failed to remove alias");
                }
                refreshAliasList();
            },
            []() {
                // No action needed when user cancels
            }
        );

        confirmWindow->set_transient_for(*this);
        confirmWindow->set_modal(true);
        confirmWindow->show();
    }


    void refreshAliasList() {
        aliases = fileManager.getAliases(selectedItem.second);
        aliasList.removeAliases();

        if (aliases.empty()) {
            update_status_label("No aliases found");
        } else {
            update_status_label(std::to_string(aliases.size()) + " aliases found");
            aliasList.addAliases(
                aliases,
                [this](const std::string& oldAlias, const std::string& newAlias, const std::string& command) {
                    saveAlias(oldAlias, newAlias, command);
                },
                [this](const std::string& alias) {
                    removeAlias(alias);
                }
            );
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

    std::function<void()> addClicked = [this]() {
        std::cout << "Add button clicked" << std::endl;
        auto newAliasWindow = new NewAliasWindow(
            [this](std::string alias, std::string command) {
                bool success = fileManager.appendAlias(selectedItem.second, alias, command);
                if (success) {
                    update_status_label("Alias added successfully");
                }
                return success;
            },
            [this]() {
                refreshAliasList();
            }
        );
        newAliasWindow->set_transient_for(*this);
        newAliasWindow->set_modal(true);
        newAliasWindow->show();
    };


};

#endif
