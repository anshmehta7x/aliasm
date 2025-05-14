#include "gtkmm/button.h"
#include <functional>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>

using namespace Gtk;

class NewAliasWindow : public Window{

    public:

    Box n_box;
    Label aliasLabel;
    Label commandLabel;

    Entry aliasEntry;
    Entry commandEntry;

    Button addButton;

    NewAliasWindow(const std::function<void()> &callback) : n_box(Gtk::Orientation::VERTICAL, 10){
        set_title("Add New Alias");
        set_default_size(300, 200);
        set_resizable(false);
        set_child(n_box);

        aliasLabel.set_text("Alias:");
        commandLabel.set_text("Command:");
        addButton.set_label("Add Alias");

        n_box.append(aliasLabel);
        n_box.append(aliasEntry);
        n_box.append(commandLabel);
        n_box.append(commandEntry);
        n_box.append(addButton);

        addButton.signal_clicked().connect(callback);
    }
};
