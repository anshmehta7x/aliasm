#include <gtkmm/button.h>

class AddButton : public Gtk::Button {
public:
    AddButton() : Gtk::Button("+") {
        set_margin(10);
        set_hexpand(true);
    }
    
    void set_on_click(std::function<void()> callback) {
        signal_clicked().connect(callback);
    }
};
