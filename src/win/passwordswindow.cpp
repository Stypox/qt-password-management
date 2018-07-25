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
}

void PasswordsWindow::loadData() {
	LoginDialog loginDialog(m_settings, m_passwords);
	loginDialog.exec();
	if (!m_settings.loaded)
		exit(0);
	m_settings.debug();
}

PasswordsWindow::~PasswordsWindow() {
	delete ui;
}
