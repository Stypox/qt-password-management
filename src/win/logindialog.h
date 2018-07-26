#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QVector>
#include "src/res/settings.h"
#include "src/res/password.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
	Q_OBJECT

public:
	explicit LoginDialog(Settings& settings, UserData& userData, QVector<Password>& passwords, QWidget *parent = nullptr);
	~LoginDialog();

private slots:
	void login();
	void create();
	void changeLanguage(int index);

private:
	void updateLabels();
	void setError(const QString& key);
	void setWarning(const QString& key);

	Ui::LoginDialog *ui;
	Settings& m_settings;
	UserData& m_userData;
	QVector<Password>& m_passwords;

	QByteArray creatingPassword;
};

#endif // LOGINDIALOG_H
