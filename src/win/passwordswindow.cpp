#include "passwordswindow.h"
#include "ui_passwordswindow.h"
#include "src/res/resources.h"

PasswordsWindow::PasswordsWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::PasswordsWindow) {
    ui->setupUi(this);

    ui->addPassword->setFont(toolButtonsFont);
    ui->help->setFont(toolButtonsFont);
    ui->settings->setFont(toolButtonsFont);
    ui->logout->setFont(toolButtonsFont);

    LoginDialog loginDialog(m_settings, m_passwords);
    loginDialog.exec();
}

PasswordsWindow::~PasswordsWindow() {
    delete ui;
}
