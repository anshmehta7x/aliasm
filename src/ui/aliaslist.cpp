#include "aliaslist.h"
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

AliasList::AliasList() : Gtk::Box(Gtk::Orientation::VERTICAL, 10) {
    set_margin(10);
}

void AliasList::addAliases(const std::vector<std::pair<std::string, std::string>>& aliases,
                           SaveCallback saveCallback,
                           RemoveCallback removeCallback) {
    for (const auto& alias : aliases) {
        auto row = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);

        auto aliasEntry = Gtk::make_managed<Gtk::Entry>();
        aliasEntry->set_text(alias.first);
        aliasEntry->set_width_chars(10);

        auto commandEntry = Gtk::make_managed<Gtk::Entry>();
        commandEntry->set_text(alias.second);
        commandEntry->set_width_chars(20);
        commandEntry->set_hexpand(true);

        auto saveButton = Gtk::make_managed<Gtk::Button>("Save");
        auto removeButton = Gtk::make_managed<Gtk::Button>("Remove");

        saveButton->signal_clicked().connect([=]() {
            saveCallback(alias.first, aliasEntry->get_text(), commandEntry->get_text());
        });

        removeButton->signal_clicked().connect([=]() {
            removeCallback(alias.first);
        });

        row->append(*aliasEntry);
        row->append(*commandEntry);
        row->append(*saveButton);
        row->append(*removeButton);

        append(*row);
    }
}

void AliasList::removeAliases() {
    Gtk::Widget* child = get_first_child();
    while (child) {
        Gtk::Widget* next = child->get_next_sibling();
        remove(*child);
        child = next;
    }
}
