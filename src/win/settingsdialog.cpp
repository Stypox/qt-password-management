#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(Settings& settings, UserData& userData, QWidget *parent) :
	QDialog{parent}, ui{new Ui::SettingsDialog},
	m_settings{settings}, m_userData{userData},
	m_settingsCopy{settings}, m_userDataCopy{userData} {
	ui->setupUi(this);

	connect(ui->)
}
SettingsDialog::~SettingsDialog() {
	delete ui;
}
