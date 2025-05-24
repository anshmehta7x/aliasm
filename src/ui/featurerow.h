#ifndef ALIASM_UI_ADDBUTTON_H
#define ALIASM_UI_ADDBUTTON_H

#include "gtkmm/button.h"
#include <gtkmm/box.h>
#include <functional>

class FeatureButtonRow : public Gtk::Box {
public:
    Gtk::Button addButton;
    Gtk::Button exportButton;
    Gtk::Button importButton;
    FeatureButtonRow();
    void set_addbtn_on_click(std::function<void()> callback);
    void set_exportbtn_on_click(std::function<void()> callback);
    void set_importbtn_on_click(std::function<void()> callback);
};

#endif
