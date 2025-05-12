#ifndef ALIASM_UI_ALIASLIST_H
#define ALIASM_UI_ALIASLIST_H

#include "gtkmm/widget.h"
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <vector>
#include <string>
#include <utility>

class AliasList : public Gtk::Box {
public:
AliasList() :
        Gtk::Box(Gtk::Orientation::VERTICAL, 10)
    {
        set_margin(10);
    }

    void addAliases(const std::vector<std::pair<std::string, std::string>>& aliases){
        for (const auto& alias : aliases) {
            auto aliasLabel = Gtk::make_managed<Gtk::Label>(alias.first + " = " + alias.second);
            aliasLabel->set_margin(10);
            aliasLabel->set_halign(Gtk::Align::START);
            append(*aliasLabel);
        }
    }

    void removeAliases(){
        Gtk::Widget *child = get_first_child();
        while (child) {
            Gtk::Widget *next = child->get_next_sibling();
            remove(*child);
            child = next;
        }
    }
};

#endif // ALIASM_UI_ALIASLIST_H
