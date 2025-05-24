#include "confirm.h"

ConfirmWindow::ConfirmWindow(const std::string& message,
                             const std::function<void()>& yesCallback,
                             const std::function<void()>& noCallback)
    : c_box(Gtk::Orientation::VERTICAL, 10) {

    set_title("Confirmation");
    set_default_size(300, 100);
    set_resizable(false);
    set_child(c_box);

    confirmLabel.set_text(message);
    c_box.append(confirmLabel);

    yesButton.set_label("Yes");
    noButton.set_label("No");

    c_box.append(yesButton);
    c_box.append(noButton);

    yesButton.signal_clicked().connect([this, yesCallback]() {
        yesCallback();
        close();
    });

    noButton.signal_clicked().connect([this, noCallback]() {
        noCallback();
        close();
    });
}
