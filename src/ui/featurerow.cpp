#include "featurerow.h"
#include <gtkmm/settings.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/styleprovider.h>
#include <iostream>

FeatureButtonRow::FeatureButtonRow() : Gtk::Box(Gtk::Orientation::HORIZONTAL,10), isDarkTheme(true) {
    addButton.set_label("+");
    exportButton.set_label("Export");
    importButton.set_label("Import");
    addButton.set_hexpand(true);
    exportButton.set_hexpand(true);
    themeToggleButton.set_label("☀️");
    themeToggleButton.set_tooltip_text("Toggle Dark/Light Theme");
    themeToggleButton.signal_clicked().connect(sigc::mem_fun(*this, &FeatureButtonRow::toggleTheme));

    append(addButton);
    append(importButton);
    append(exportButton);
    append(themeToggleButton);
    set_margin(10);
    set_hexpand(true);

    // Initialize CSS provider
    cssProvider = Gtk::CssProvider::create();

    // Apply initial theme when widget is realized
    signal_realize().connect([this]() {
        applyCurrentTheme();
    });
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

void FeatureButtonRow::toggleTheme() {
    isDarkTheme = !isDarkTheme;
    themeToggleButton.set_label(isDarkTheme ? "☀️" : "🌙");
    applyCurrentTheme();
    std::cout << "Dark mode: " << isDarkTheme << std::endl;
}

void FeatureButtonRow::applyCurrentTheme() {
    auto display = get_display();
    if (!display) {
        std::cout << "No display available" << std::endl;
        return;
    }

    std::string css_content;
    if (isDarkTheme) {
        css_content = R"(
            window {
                background-color: #2e2e2e;
                color: #ffffff;
            }

            button {
                background-color: #484848;
                border: 1px solid #666666;
                color: #ffffff;
                border-radius: 4px;
                padding: 8px 16px;
            }

            button:hover {
                background-color: #555555;
            }

            button:active {
                background-color: #333333;
            }

            /* Entry (text input) styling */
            entry {
                background-color: #3c3c3c;
                border: 1px solid #666666;
                color: #ffffff;
                border-radius: 4px;
                padding: 8px;
            }

            entry:focus {
                border-color: #888888;
                background-color: #404040;
            }

            /* ComboBox styling */
            combobox {
                background-color: #3c3c3c;
                border: 1px solid #666666;
                color: #ffffff;
                border-radius: 4px;
            }

            combobox button {
                background-color: #484848;
                border: none;
                color: #ffffff;
            }

            /* Dropdown menu styling */
            popover {
                background-color: #3c3c3c;
                border: 1px solid #666666;
                color: #ffffff;
            }

            popover listview {
                background-color: #3c3c3c;
                color: #ffffff;
            }

            popover listview row {
                background-color: transparent;
                color: #ffffff;
                padding: 8px;
            }

            popover listview row:hover {
                background-color: #484848;
            }

            popover listview row:selected {
                background-color: #555555;
            }
        )";
    } else {
        css_content = R"(
            window {
                background-color: #ffffff;
                color: #000000;
            }

            button {
                background-color: #f0f0f0;
                border: 1px solid #cccccc;
                color: #000000;
                border-radius: 4px;
                padding: 8px 16px;
            }

            button:hover {
                background-color: #e0e0e0;
            }

            button:active {
                background-color: #d0d0d0;
            }

            /* Entry (text input) styling */
            entry {
                background-color: #ffffff;
                border: 1px solid #cccccc;
                color: #000000;
                border-radius: 4px;
                padding: 8px;
            }

            entry:focus {
                border-color: #0078d4;
                background-color: #ffffff;
            }

            /* ComboBox styling */
            combobox {
                background-color: #ffffff;
                border: 1px solid #cccccc;
                color: #000000;
                border-radius: 4px;
            }

            combobox button {
                background-color: #f0f0f0;
                border: none;
                color: #000000;
            }

            /* Dropdown menu styling */
            popover {
                background-color: #3c3c3c;
                border: 1px solid #666666;
                color: #ffffff;
            }

            popover listview {
                background-color: #3c3c3c;
                color: #ffffff;
            }

            popover listview row {
                background-color: transparent;
                color: #ffffff;
                padding: 8px;
            }

            popover listview row:hover {
                background-color: #484848;
            }

            popover listview row:selected {
                background-color: #555555;
            }
        )";
    }

    try {
        cssProvider->load_from_data(css_content);
        Gtk::StyleContext::add_provider_for_display(
            display,
            cssProvider,
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
        std::cout << "Theme applied successfully" << std::endl;
    } catch (const Glib::Error& ex) {
        std::cerr << "CSS Error: " << ex.what() << std::endl;
    }
}
