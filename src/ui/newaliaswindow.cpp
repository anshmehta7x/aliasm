#include "newaliaswindow.h"

NewAliasWindow::NewAliasWindow(const std::function<bool(std::string, std::string)>& callback,
                               const std::function<void()>& refreshCallback)
    : n_box(Gtk::Orientation::VERTICAL, 10)
{
    set_title("Add New Alias");
    set_default_size(300, 200);
    set_resizable(false);
    set_child(n_box);

    aliasLabel.set_text("Alias:");
    commandLabel.set_text("Command:");
    update_status_label("");
    statusLabel.set_margin(10);
    addButton.set_label("Add Alias");

    n_box.append(aliasLabel);
    n_box.append(aliasEntry);
    n_box.append(commandLabel);
    n_box.append(commandEntry);
    n_box.append(statusLabel);
    n_box.append(addButton);

    addButton.signal_clicked().connect([this, callback, refreshCallback]() {
        if (aliasEntry.get_text().empty() || commandEntry.get_text().empty()) {
            update_status_label("Alias and command cannot be empty");
            return;
        }

        if (callback(aliasEntry.get_text(), commandEntry.get_text())) {
            refreshCallback();
            close();
        } else {
            update_status_label("Failed to add alias");
        }
    });
}

void NewAliasWindow::update_status_label(std::string newText) {
    statusLabel.set_visible(true);
    statusLabel.set_text(newText);
    Glib::signal_timeout().connect_once([this]() {
        statusLabel.set_visible(false);
    }, 2000);
}
