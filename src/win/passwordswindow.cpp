#include "passwordswindow.h"
#include "ui_passwordswindow.h"
#include <QMessageBox>
#include <QPalette>
#include <QDebug>
#include "src/res/resources.h"
#include "src/res/cryptography.h"
#include "src/res/passwordwidget.h"
#include "logindialog.h"
#include "addeditdialog.h"
#include "settingsdialog.h"
#include "infodialog.h"

	ui->setupUi(this);
	ui->newPassword->setFont(res::iconFont);
	ui->info->setFont(res::iconFont);
	ui->usernameViewer->setText(res::passwordsLabels[res::config.language()]["usernameDefault"]);
	ui->settings->setFont(res::iconFont);
	ui->logout->setFont(res::iconFont);

	connect(ui->newPassword, SIGNAL(clicked(bool)), this, SLOT(newPassword()));
	connect(ui->info, SIGNAL(clicked(bool)), this, SLOT(info()));
	connect(ui->settings, SIGNAL(clicked(bool)), this, SLOT(settings()));
	connect(ui->logout, SIGNAL(clicked(bool)), this, SLOT(logout()));

	ui->passwordList->setDragDropMode(QAbstractItemView::InternalMove);
	ui->passwordList->setDragEnabled(true);
	updateLabels();
	updateColors();
}
PasswordsWindow::~PasswordsWindow() {
	m_settings.debug();
	for (auto&& password : m_passwords)
		password.debug();

	saveData();
	delete ui;
}

void PasswordsWindow::loadData() {
	LoginDialog loginDialog{m_settings, m_userData, m_passwords};
	loginDialog.exec();
	if (!m_settings.loaded)
		exit(0);

	m_settings.debug();
	for (auto&& password : m_passwords)
		password.debug();

	updateLabels();
	updateColors();
	updatePasswords();
}

void PasswordsWindow::saveData() {
	if (m_settings.loaded) {
		QFile dataFile{res::config.dataDir() + m_userData.username + res::dataFileExt};
		dataFile.open(QIODevice::WriteOnly);
		dataFile.write(res::encrypt(buildData(m_settings, m_passwords), m_userData.password));
	}
}
void PasswordsWindow::updateLabels() {
	const QHash<QString, QString>& labels {res::passwordsLabels[m_settings.loaded ? m_settings.language : res::config.language()]};
	if (m_settings.loaded) {
		setWindowTitle(labels["windowTitle"].arg(m_userData.username));
		ui->usernameViewer->setText(m_userData.username);
	}
	else {
		setWindowTitle(labels["defaultWindowTitle"]);
		ui->usernameViewer->setText(labels["usernameDefault"]);
	}
}
void PasswordsWindow::updateColors() {
	if (m_settings.loaded && m_settings.darkThemeActive)
		m_app.setStyleSheet(res::darkTheme);
	else
		m_app.setStyleSheet("");
}
void PasswordsWindow::updatePasswords() {
	QVector<bool> widgetsOpened;
	widgetsOpened.reserve(m_widgets.size());
	for (auto&& widget : m_widgets) {
		widgetsOpened.push_back(widget->isOpened());
	}

	m_widgets.resize(0);
	for (int passwordIndex = 0; passwordIndex < m_passwords.size(); ++passwordIndex) {
		m_widgets.push_back(std::shared_ptr<PasswordWidget>{new PasswordWidget
			{passwordIndex, m_passwords[passwordIndex], m_settings, this, widgetsOpened.value(passwordIndex)}});
	}

	ui->passwordList->clear();
	for (int widgetIndex = 0; widgetIndex < m_widgets.size(); ++widgetIndex) {
		ui->passwordList->insertItem(widgetIndex, "");
		ui->passwordList->setItemWidget(ui->passwordList->item(widgetIndex), m_widgets[widgetIndex].get());
		ui->passwordList->item(widgetIndex)->setSizeHint({0, m_widgets[widgetIndex]->getHeight()});
	}
}


void PasswordsWindow::newPassword() {
	AddEditDialog addEditDialog{m_settings, this};
	addEditDialog.exec();
}
void PasswordsWindow::info() {
	InfoDialog infoDialog{m_passwords, m_settings};
	infoDialog.exec();
}
void PasswordsWindow::settings() {
	SettingsDialog settingsDialog{m_settings, m_userData, m_passwords, m_app};
	settingsDialog.exec();
	saveData();
	updateLabels();
	updatePasswords();
}
void PasswordsWindow::logout() {
	saveData();

	m_passwords.resize(0);
	updateLabels();
	updateColors();
	updatePasswords();

	loadData();
}

void PasswordsWindow::addPassword(Password password) {
	m_passwords.push_back(password);
	m_widgets.push_back(std::shared_ptr<PasswordWidget>(new PasswordWidget{m_widgets.size(), password, m_settings, this}));
	saveData();
	updatePasswords();
}

void PasswordsWindow::editPassword(int index) {
	AddEditDialog addEditDialog{&m_passwords[index], m_settings, this};
	addEditDialog.exec();
	saveData();
}
void PasswordsWindow::removePassword(int index) {
	if (!m_settings.removalConfirmationDialogActive ||
		QMessageBox::question(this,
			QString{res::passwordsLabels[m_settings.language]["questionRemovalTitle"]}.arg(m_passwords.at(index).name),
			QString{res::passwordsLabels[m_settings.language]["questionRemoval"]}.arg(m_passwords.at(index).name))
		== QMessageBox::Yes) {
		m_passwords.removeAt(index);
		m_widgets.removeAt(index);
		saveData();
		updatePasswords();
	}
}
void PasswordsWindow::changeItemSize(int index, QSize size) {
	ui->passwordList->item(index)->setSizeHint(size);
}


