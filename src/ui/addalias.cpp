#include "addalias.h"

AddButton::AddButton() : Gtk::Button("+") {
    set_margin(10);
    set_hexpand(true);
}

void AddButton::set_on_click(std::function<void()> callback) {
    signal_clicked().connect(callback);
}
