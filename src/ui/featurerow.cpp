#include "featurerow.h"
#include <gtkmm/button.h>

FeatureButtonRow::FeatureButtonRow() : Gtk::Box(Gtk::Orientation::HORIZONTAL,10) {
    addButton.set_label("+");
    exportButton.set_label("Export");
    importButton.set_label("Import");
    addButton.set_hexpand(true);
    exportButton.set_hexpand(true);

    append(addButton);
    append(importButton);
    append(exportButton);

    set_margin(10);
    set_hexpand(true);
}

void FeatureButtonRow::set_addbtn_on_click(std::function<void()> callback) {
    addButton.signal_clicked().connect(callback);
}

void FeatureButtonRow::set_exportbtn_on_click(std::function<void()> callback) {
    exportButton.signal_clicked().connect(callback);
}

void FeatureButtonRow::set_importbtn_on_click(std::function<void()> callback) {
    importButton.signal_clicked().connect(callback);
}
