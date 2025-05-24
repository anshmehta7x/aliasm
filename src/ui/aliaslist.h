#ifndef ALIASM_UI_ALIASLIST_H
#define ALIASM_UI_ALIASLIST_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <vector>
#include <string>
#include <utility>
#include <functional>

class AliasList : public Gtk::Box {
public:
    using SaveCallback = std::function<void(const std::string&, const std::string&, const std::string&)>;
    using RemoveCallback = std::function<void(const std::string&)>;

    AliasList();

    void addAliases(const std::vector<std::pair<std::string, std::string>>& aliases,
                    SaveCallback saveCallback,
                    RemoveCallback removeCallback);

    void removeAliases();
};

#endif
