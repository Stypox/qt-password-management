#include "passwordswindow.h"
#include "ui_passwordswindow.h"
#include "src/res/resources.h"

PasswordsWindow::PasswordsWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::PasswordsWindow) {
    ui->setupUi(this);

    ui->addPassword->setFont(res::iconFont);
    ui->help->setFont(res::iconFont);
    ui->settings->setFont(res::iconFont);
    ui->logout->setFont(res::iconFont);

    LoginDialog loginDialog(m_settings, m_passwords);
    loginDialog.exec();
}

PasswordsWindow::~PasswordsWindow() {
    delete ui;
}
