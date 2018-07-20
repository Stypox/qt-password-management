#include "logindialog.h"
#include "ui_logindialog.h"
#include "src/res/resources.h"

LoginDialog::LoginDialog(Settings& settings, QVector<Password>& passwords, QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginDialog), m_settings(settings), m_passwords(passwords) {
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif

    ui->passwordEditor->setEchoMode(QLineEdit::Password);
    //editPassword->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}
LoginDialog::~LoginDialog() {
    delete ui;
}

void login() {

}
void create() {

}
