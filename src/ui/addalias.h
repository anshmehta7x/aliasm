#ifndef ALIASM_UI_ADDBUTTON_H
#define ALIASM_UI_ADDBUTTON_H

#include <gtkmm/button.h>
#include <functional>

class AddButton : public Gtk::Button {
public:
    AddButton();
    void set_on_click(std::function<void()> callback);
};

#endif
