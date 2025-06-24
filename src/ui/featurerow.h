#ifndef FEATUREROW_H
#define FEATUREROW_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <functional>

class FeatureButtonRow : public Gtk::Box {
public:
    FeatureButtonRow();
    void set_addbtn_on_click(std::function<void()> callback);
    void set_exportbtn_on_click(std::function<void()> callback);
    void set_importbtn_on_click(std::function<void()> callback);

private:
    Gtk::Button addButton;
    Gtk::Button exportButton;
    Gtk::Button importButton;
    Gtk::Button themeToggleButton;

    bool isDarkTheme;
    Glib::RefPtr<Gtk::CssProvider> cssProvider;

    void toggleTheme();
    void setupTheme();
    void applyCurrentTheme();
};

#endif
