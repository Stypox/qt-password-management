#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include "src/res/resources.h"
#include "src/res/cryptography.h"

LoginDialog::LoginDialog(Settings& settings, UserData& userData, QVector<Password>& passwords, QWidget *parent) :
	QDialog(parent), ui(new Ui::LoginDialog), m_settings(settings), m_userData(userData), m_passwords(passwords) {
	ui->setupUi(this);	
	setInputMethodHints(res::inputMethod);
#if OS_MOBILE
	setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

	m_settings.reset();
	m_passwords.resize(0);

	ui->passwordEditor->setEchoMode(QLineEdit::Password);
	setError("noError");
	setWarning("noWarning");
	ui->languageEditor->clear();
	for (res::Lang langIndex = res::Lang::min; langIndex <= res::Lang::max; ++langIndex)
		ui->languageEditor->addItem(res::sharedLabels[langIndex]["langName"]);
	ui->languageEditor->setCurrentIndex(static_cast<int>(res::config.language()));
	updateLabels();

	connect(ui->create, SIGNAL(clicked(bool)), this, SLOT(create()));
	connect(ui->login, SIGNAL(clicked(bool)), this, SLOT(login()));
	connect(ui->languageEditor, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLanguage(int)));
}
LoginDialog::~LoginDialog() {
	delete ui;
}

void LoginDialog::login() {
	const QString& username = ui->usernameEditor->text();
	const QByteArray& password = ui->passwordEditor->text().toUtf8();
	if (password.length() < res::passwordMinLen || password.length() > res::passwordMaxLen) {
		setError("errInvalidPassword");
		return;
	}

	QFile dataFile(res::config.dataDir() + username + res::dataFileExt);
	if (dataFile.open(QIODevice::ReadOnly)) {
		SimpleCrypt::Error success;
		QByteArray data = res::decrypt(dataFile.readAll(), password, success);

		switch (success) {
		case SimpleCrypt::ErrorUnknownVersion:
			setError("errCorruptedFile");
			return;
		case SimpleCrypt::ErrorIntegrityFailed:
			setError("errInvalidFile");
			return;
		default:
			break;
		}

		if (!extractData(data, m_settings, m_passwords)) {
			setError("errCorruptedData");
			return;
		}
		m_userData = UserData{username, password};

		close();
	}
	else {
		setError("errFileNotFound");
		return;
	}
}
void LoginDialog::create() {
	const QString& username = ui->usernameEditor->text();
	const QByteArray& password = ui->passwordEditor->text().toUtf8();

	if (creatingPassword.isEmpty()) {
		if (password.length() < res::passwordMinLen || password.length() > res::passwordMaxLen) {
			setError("errInvalidPassword");
			return;
		}

		QFile dataFile {res::config.dataDir() + username + res::dataFileExt};
		if (dataFile.exists())
			setError("errExistingAccount");

		creatingPassword = password;
		ui->passwordEditor->clear();
		ui->usernameEditor->setDisabled(true);
		setWarning("warReinsertPassword");
	}
	else {
		if (password != creatingPassword) {
			creatingPassword = "";
			ui->usernameEditor->setDisabled(false);
			setWarning("noWarning");
			setError("errPasswordsNotMatching");
			return;
		}

		m_settings.load(res::config.language());
		m_userData = UserData{username, password};

		QFile dataFile {res::config.dataDir() + username + res::dataFileExt};
		if (dataFile.exists()) {
			QFile backupFile{res::config.dataDir() + username + res::backupFileExt};
			backupFile.open(QIODevice::WriteOnly);
			dataFile.open(QIODevice::ReadOnly);
			backupFile.write(dataFile.readAll());
		}

		close();
	}
}
void LoginDialog::changeLanguage(int index){
	res::config.setLanguage(static_cast<res::Lang>(index));
	updateLabels();
}

void LoginDialog::updateLabels() {
	const QHash<QString, QString>& labels = res::loginLabels[res::config.language()];
	ui->usernameTitle->setText(labels["usernameTitle"]);
	ui->passwordTitle->setText(labels["passwordTitle"]);
	ui->create->setText(labels["create"]);
	ui->login->setText(labels["login"]);
}
void LoginDialog::setError(const QString& key) {
	qDebug() << "Login window error:" << key;
	ui->errorMessage->setText(res::loginLabels[res::config.language()][key]);
}
void LoginDialog::setWarning(const QString& key) {
	qDebug() << "Login window warning:" << key;
	ui->warningMessage->setText(res::loginLabels[res::config.language()][key]);
}
