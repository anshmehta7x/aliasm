#ifndef ALIASM_UI_NEWALIASWINDOW_H
#define ALIASM_UI_NEWALIASWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <glibmm/main.h>
#include <functional>
#include <string>

class NewAliasWindow : public Gtk::Window {
public:
    NewAliasWindow(const std::function<bool(std::string, std::string)>& callback,
                   const std::function<void()>& refreshCallback);

private:
    Gtk::Box n_box;
    Gtk::Label aliasLabel;
    Gtk::Label commandLabel;
    Gtk::Label statusLabel;
    Gtk::Entry aliasEntry;
    Gtk::Entry commandEntry;
    Gtk::Button addButton;

    void update_status_label(std::string newText);
};

#endif
