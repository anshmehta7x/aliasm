#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/stringlist.h>
#include <iostream>
#include <stdexcept>
#include <utility>


class MainWindow : public Gtk::Window {
public:

    Gtk::DropDown dropdown;
    std::pair<Glib::ustring, std::string> selectedItem; // stores shell , filename

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
        std::cout<<selectedItem.first<<" "<<selectedItem.second<<std::endl;
    }


    std::string getFilename(Glib::ustring shell){
        if(shell == "zsh"){
            return ".zshrc";
        }
        else if(shell == "bash"){
            return ".bashrc";
        }
        else{
            throw std::runtime_error("Unknown shell type");
        }
    }

    void addDropdown(std::vector<Glib::ustring> items){

        dropdown = Gtk::DropDown(items);
        dropdown.set_selected(0);
        std::string filename;
        selectedItem = std::make_pair(items[0], getFilename(items[0]));
        set_child(dropdown);

    }

    virtual ~MainWindow() {}
};
