#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dropdown.h>
#include <iostream>


class MainWindow : public Gtk::Window {
public:

    Gtk::DropDown dropdown;


    MainWindow(std::vector<Glib::ustring> items) {
        set_title("Alias Manager");
        set_default_size(300, 200);
        set_resizable(true);
        if(items.size() == 0){
            Gtk::Label label = Gtk::Label(".bashrc or .zshrc not found");
            set_child(label);        }
        else{
            addDropdown(items);
        }

    }

    void addDropdown(std::vector<Glib::ustring> items){

        dropdown = Gtk::DropDown(items);
        dropdown.set_selected(0);
        set_child(dropdown);

    }

    virtual ~MainWindow() {}
};
