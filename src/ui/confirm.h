#ifndef ALIASM_UI_CONFIRM_H
#define ALIASM_UI_CONFIRM_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <functional>
#include <string>

class ConfirmWindow : public Gtk::Window {
public:
    ConfirmWindow(const std::string& message,
                  const std::function<void()>& yesCallback,
                  const std::function<void()>& noCallback);

private:
    Gtk::Box c_box;
    Gtk::Label confirmLabel;
    Gtk::Button yesButton;
    Gtk::Button noButton;
};

#endif
