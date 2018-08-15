#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QInputDialog>
#include "src/res/cryptography.h"

SettingsDialog::SettingsDialog(Settings& settings, UserData& userData, const QVector<Password>& passwords, QApplication& app, QWidget *parent) :
	QDialog{parent}, ui{new Ui::SettingsDialog}, m_app{app},
	m_settings{settings}, m_userData{userData}, m_passwords{passwords},
	m_settingsChanged{false}
{
	ui->setupUi(this);
#if OS_MOBILE
	setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif

	updateLabels();

	connect(ui->backup, SIGNAL(clicked(bool)), this, SLOT(backup()));
	connect(ui->resetSettings, SIGNAL(clicked(bool)), this, SLOT(resetSettings()));
	connect(ui->ok, SIGNAL(clicked(bool)), this, SLOT(ok()));
	connect(ui->cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
	connect(ui->apply, SIGNAL(clicked(bool)), this, SLOT(apply()));

	connect(ui->passwordEditor, SIGNAL(textChanged(QString)), this, SLOT(passwordChanged()));
	connect(ui->reinsertPasswordEditor, SIGNAL(textChanged(QString)), this, SLOT(passwordChanged()));

	connect(ui->languageEditor, SIGNAL(currentIndexChanged(int)), this, SLOT(settingsChanged()));
	connect(ui->darkTheme, SIGNAL(clicked(bool)), this, SLOT(settingsChanged()));
	connect(ui->removalConfirmationDialog, SIGNAL(clicked(bool)), this, SLOT(settingsChanged()));
	connect(ui->pwned, SIGNAL(clicked(bool)), this, SLOT(settingsChanged()));
	connect(ui->passwordEditor, SIGNAL(textChanged(QString)), this, SLOT(settingsChanged()));
	connect(ui->reinsertPasswordEditor, SIGNAL(textChanged(QString)), this, SLOT(settingsChanged()));
}
SettingsDialog::~SettingsDialog() {
	delete ui;
}

void SettingsDialog::updateLabels() {
	passwordChanged();

	ui->languageEditor->clear();
	for (res::Lang language = res::Lang::min; language <= res::Lang::max; ++language) {
		ui->languageEditor->addItem(res::sharedLabels[language]["langName"]);
	}

	const QHash<QString, QString>& labels = res::settingsLabels[m_settings.language];
	setWindowTitle(labels["windowTitle"]);

	ui->languageTitle->setText(labels["languageTitle"]);
	ui->darkTheme->setText(labels["darkThemeTitle"]);
	ui->removalConfirmationDialog->setText(labels["removalConfirmationDialogTitle"]);
	ui->pwned->setText(labels["pwnedTitle"]);
	ui->passwordTitle->setText(labels["passwordTitle"]);
	ui->reinsertPasswordTitle->setText(labels["reinsertPasswordTitle"]);
	ui->backup->setText(labels["backup"]);
	ui->resetSettings->setText(labels["resetSettings"]);
	ui->ok->setText(labels["ok"]);
	ui->cancel->setText(labels["cancel"]);
	ui->apply->setText(labels["apply"]);

	ui->languageEditor->setCurrentIndex(static_cast<int>(m_settings.language));
	ui->darkTheme->setChecked(m_settings.darkThemeActive);
	ui->removalConfirmationDialog->setChecked(m_settings.removalConfirmationDialogActive);
	ui->pwned->setChecked(m_settings.pwnedActive);
	ui->passwordEditor->setText("");
	ui->reinsertPasswordEditor->setText("");
}
void SettingsDialog::setError(const QString& key) {
	ui->errorMessage->setText(res::settingsLabels[m_settings.language][key]);
}


void SettingsDialog::backup() {
	QFile dataFile{res::config.dataDir() + m_userData.username + res::backupFileExt};
	dataFile.open(QIODevice::WriteOnly);
	dataFile.write(res::encrypt(buildData(m_settings, m_passwords), m_userData.password));
	dataFile.close();
}
void SettingsDialog::resetSettings() {
	m_settings = Settings{};
}

void SettingsDialog::ok() {
	if (apply())
		close();
}
bool SettingsDialog::apply() {
	if (!m_settingsChanged)
		return true;
	QByteArray newPassword = ui->passwordEditor->text().toUtf8();
	if (newPassword == ui->reinsertPasswordEditor->text()) {
		if (!newPassword.isEmpty() && (newPassword.length() < res::passwordMinLen || newPassword.length() > res::passwordMaxLen))
			return false;
	}

	while (1) {
		bool ok;
		QString password = QInputDialog::getText(this, res::settingsLabels[m_settings.language]["passwordRequestWindowTitle"], res::settingsLabels[m_settings.language]["passwordRequestTitle"], QLineEdit::Password, "", &ok);
		if (ok) {
			if (password == m_userData.password)
				break;
		}
		else
			return false;
	}

	m_settings.language = static_cast<res::Lang>(ui->languageEditor->currentIndex());

	bool oldDarkThemeActive{m_settings.darkThemeActive};
	m_settings.darkThemeActive = ui->darkTheme->isChecked();
	if (oldDarkThemeActive != m_settings.darkThemeActive) {
		if (m_settings.darkThemeActive)
			m_app.setStyleSheet(res::darkTheme);
		else
			m_app.setStyleSheet("");
	}

	m_settings.removalConfirmationDialogActive = ui->removalConfirmationDialog->isChecked();
	m_settings.pwnedActive = ui->pwned->isChecked();
	if (!newPassword.isEmpty())
		m_userData.password = newPassword;

	QFile dataFile{res::config.dataDir() + m_userData.username + res::dataFileExt};
	dataFile.open(QIODevice::WriteOnly);
	dataFile.write(res::encrypt(buildData(m_settings, m_passwords), m_userData.password));
	dataFile.close();

	updateLabels();
	m_settingsChanged = false;
	ui->backup->setEnabled(true);
	return true;
}

void SettingsDialog::passwordChanged() {
	QByteArray newPassword = ui->passwordEditor->text().toUtf8();
	QByteArray reinsertPassword = ui->passwordEditor->text().toUtf8();

	if (newPassword.isEmpty() && reinsertPassword.isEmpty())
		setError("noError");
	else if (newPassword != reinsertPassword)
		setError("errPasswordsNotMatching");
	else if (newPassword.length() < res::passwordMinLen || newPassword.length() > res::passwordMaxLen)
		setError("errInvalidPassword");
	else
		setError("noError");
}
void SettingsDialog::settingsChanged() {
	m_settingsChanged = true;
	ui->backup->setEnabled(false);
}
