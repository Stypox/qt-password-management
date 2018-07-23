#include "logindialog.h"
#include "ui_logindialog.h"
#include "src/res/resources.h"
#include <QDir>

LoginDialog::LoginDialog(Settings& settings, QVector<Password>& passwords, QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginDialog), m_settings(settings), m_passwords(passwords) {
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif

	ui->passwordEditor->setEchoMode(QLineEdit::Password);
}
LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::login() {
    QFile dataFile(res::dataPath);
	if (!dataFile.open(QIODevice::ReadOnly)) {
		//setError();
    }
}
void LoginDialog::create() {

}

void LoginDialog::setError(const QString& error) {
	ui->errorMessage->setText(error);
}
