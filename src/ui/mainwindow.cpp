#include "mainwindow.h"
#include "newaliaswindow.h"
#include "confirm.h"
#include "export.h"
#include <iostream>
#include <stdexcept>

MainWindow::MainWindow(std::vector<Glib::ustring> items)
    : m_box(Gtk::Orientation::VERTICAL, 10)
{
    set_title("Alias Manager");
    set_default_size(500, 400);
    set_resizable(true);
    set_child(m_box);

    statusLabel.set_margin(10);
    scrolled.set_child(aliasList);
    scrolled.set_vexpand(true);
    scrolled.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);

    addClicked = [this]() {
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


    exportClicked = [this]() {
        std::cout << "Export button clicked" << std::endl;
        auto exportWindow = new ExportWindow(aliases);
        exportWindow->set_transient_for(*this);
        exportWindow->set_modal(true);
        exportWindow->show();
        // Implement export functionality here

    };

    importClicked = [this]() {
        std::cout << "Import button clicked" << std::endl;
        // Implement import functionality here
    };


    if (items.empty()) {
        update_status_label(".bashrc or .zshrc not found");
        m_box.append(statusLabel);
    } else {
        setupDropdown(items);
        m_box.append(dropdown);
        statusLabel.set_visible(false);
        add.set_addbtn_on_click(addClicked);
        add.set_exportbtn_on_click(exportClicked);
        add.set_importbtn_on_click(importClicked);
        m_box.append(statusLabel);
        m_box.append(add);
        m_box.append(scrolled);
        on_dropdown_change();
    }

    dropdown.property_selected().signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::on_dropdown_change)
    );
}

void MainWindow::update_status_label(std::string newText) {
    statusLabel.set_visible(true);
    statusLabel.set_text(newText);
    Glib::signal_timeout().connect_once([this]() {
        statusLabel.set_visible(false);
    }, 2000);
}

void MainWindow::on_dropdown_change() {
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

void MainWindow::saveAlias(const std::string& oldAlias, const std::string& newAlias, const std::string& command) {
    std::cout << "Saving: " << oldAlias << " → " << newAlias << " = " << command << std::endl;

    if (fileManager.updateAlias(selectedItem.second, oldAlias, newAlias, command)) {
        update_status_label("Alias updated successfully");
    } else {
        update_status_label("Failed to update alias");
    }
    refreshAliasList();
}

void MainWindow::removeAlias(const std::string& alias) {
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
            // No action needed
        }
    );

    confirmWindow->set_transient_for(*this);
    confirmWindow->set_modal(true);
    confirmWindow->show();
}

void MainWindow::refreshAliasList() {
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

std::string MainWindow::getFilename(Glib::ustring shell) {
    if (shell == "zsh") {
        return ".zshrc";
    } else if (shell == "bash") {
        return ".bashrc";
    } else {
        throw std::runtime_error("Unknown shell type");
    }
}

void MainWindow::setupDropdown(std::vector<Glib::ustring> items) {
    dropdown = Gtk::DropDown(items);
    dropdown.set_margin(10);
    dropdown.set_selected(0);
    selectedItem = std::make_pair(items[0], getFilename(items[0]));
}
