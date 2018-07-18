#include "passwordswindow.h"
#include "ui_passwordswindow.h"

PasswordsWindow::PasswordsWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::PasswordsWindow) {
    ui->setupUi(this);
}

PasswordsWindow::~PasswordsWindow() {
    delete ui;
}
