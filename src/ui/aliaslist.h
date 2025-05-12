#ifndef ALIASM_UI_ALIASLIST_H
#define ALIASM_UI_ALIASLIST_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <vector>
#include <string>
#include <utility>
#include <functional>

class AliasList : public Gtk::Box {
public:
    using SaveCallback = std::function<void(const std::string&, const std::string&, const std::string&)>;

    AliasList() : Gtk::Box(Gtk::Orientation::VERTICAL, 10) {
        set_margin(10);
    }

    void addAliases(const std::vector<std::pair<std::string, std::string>>& aliases, SaveCallback callback) {
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

            // std::string prevAlias = alias.first;

            saveButton->signal_clicked().connect([=]() {
                callback(alias.first, aliasEntry->get_text(), commandEntry->get_text());
                    //have to set the value of alias.first to aliasEntry->get_text() so that it updates
                    // prevAlias = aliasEntry->get_text();


            });

            row->append(*aliasEntry);
            row->append(*commandEntry);
            row->append(*saveButton);

            append(*row);
        }
    }

    void removeAliases() {
        Gtk::Widget* child = get_first_child();
        while (child) {
            Gtk::Widget* next = child->get_next_sibling();
            remove(*child);
            child = next;
        }
    }
};

#endif
