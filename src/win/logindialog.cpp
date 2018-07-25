#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include "src/res/resources.h"
#include "src/res/cryptography.h"

LoginDialog::LoginDialog(Settings& settings, QVector<Password>& passwords, QWidget *parent) :
	QDialog(parent), ui(new Ui::LoginDialog), m_settings(settings), m_passwords(passwords) {
	ui->setupUi(this);

#ifdef Q_OS_ANDROID
	setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif

	m_settings.reset();
	m_passwords.resize(0);

	ui->passwordEditor->setEchoMode(QLineEdit::Password);
	setLabError("noError");
	updateLabels();

	connect(ui->create, SIGNAL(clicked(bool)), this, SLOT(create()));
	connect(ui->login, SIGNAL(clicked(bool)), this, SLOT(login()));
}
LoginDialog::~LoginDialog() {
	delete ui;
}

void LoginDialog::login() {
	const QString& username = ui->usernameEditor->text();
	const QByteArray& password = ui->passwordEditor->text().toUtf8();
	if (password.length() < res::passwordMinLen || password.length() > res::passwordMaxLen) {
		setLabError("errInvalidPassword");
		return;
	}

	QFile dataFile(res::config.dataDir() + username + res::dataFileExt);
	if (dataFile.open(QIODevice::ReadOnly)) {
		SimpleCrypt::Error success;
		QByteArray data = res::decrypt(dataFile.readAll(), password, success);
		if (data.isEmpty()) {
			setLabError("errInvalidFile");
			return;
		}

		switch (success) {
		case SimpleCrypt::ErrorUnknownVersion:
			setLabError("errCorruptedFile");
			return;
		case SimpleCrypt::ErrorIntegrityFailed:
			setLabError("errInvalidFile");
			return;
		default:
			break;
		}

		QJsonObject json {QJsonDocument::fromJson(data).object()};
		m_settings.load(username, password, json[res::json::settings].toObject());
		for (auto&& passwordJson : json[res::json::passwordArray].toArray())
			m_passwords.push_back({passwordJson.toObject()});

		close();
	}
	else {
		setLabError("errFileNotFound");
		return;
	}
}
void LoginDialog::create() {
	const QString& username = ui->usernameEditor->text();
	const QByteArray& password = ui->passwordEditor->text().toUtf8();

	if (creatingPassword.isEmpty()) {
		if (password.length() < res::passwordMinLen || password.length() > res::passwordMaxLen) {
			setLabError("errInvalidPassword");
			return;
		}

		creatingPassword = password;
		ui->passwordEditor->clear();
		ui->usernameEditor->setDisabled(true);
		setLabError("warReinsertPassword");
	}
	else {
		if (password != creatingPassword) {
			creatingPassword = "";
			ui->usernameEditor->setDisabled(false);
			setLabError("errPasswordsNotMatching");
			return;
		}

		m_settings.load(username, password);

		QFile dataFile {res::config.dataDir() + username + res::dataFileExt};
		if (dataFile.exists()) {
			setLabError("warExistingAccount");
			QFile backupFile{res::config.dataDir() + username + res::backupFileExt};
			backupFile.open(QIODevice::WriteOnly);
			dataFile.open(QIODevice::ReadOnly);
			backupFile.write(dataFile.readAll());
		}

		close();
	}
}

void LoginDialog::updateLabels() {
	const QHash<QString, QString>& labels = res::loginLabels[res::config.language()];
	ui->usernameTitle->setText(labels["usernameTitle"]);
	ui->passwordTitle->setText(labels["passwordTitle"]);
	ui->create->setText(labels["create"]);
	ui->login->setText(labels["login"]);
}
void LoginDialog::setError(const QString& error) {
	qDebug() << "Login window error:" << error;
	ui->errorMessage->setText(error);
}
void LoginDialog::setLabError(const QString& key) {
	setError(res::loginLabels[res::config.language()][key]);
}
