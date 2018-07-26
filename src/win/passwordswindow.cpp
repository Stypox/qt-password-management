#include "passwordswindow.h"
#include "ui_passwordswindow.h"
#include "src/res/resources.h"
#include "src/res/cryptography.h"

PasswordsWindow::PasswordsWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::PasswordsWindow) {
	ui->setupUi(this);

	ui->addPassword->setFont(res::iconFont);
	ui->help->setFont(res::iconFont);
	ui->settings->setFont(res::iconFont);
	ui->logout->setFont(res::iconFont);
}

void PasswordsWindow::loadData() {
	LoginDialog loginDialog(m_settings, m_userData, m_passwords);
	loginDialog.exec();
	if (!m_settings.loaded)
		exit(0);
	m_settings.debug();
}
void PasswordsWindow::saveData() {
	if (m_settings.loaded) {
		QFile dataFile{res::config.dataDir() + m_userData.username + res::dataFileExt};
		dataFile.open(QIODevice::WriteOnly);
		dataFile.write(res::encrypt(buildData(m_settings, m_passwords), m_userData.password));
	}
}

PasswordsWindow::~PasswordsWindow() {
	saveData();
	delete ui;
}
