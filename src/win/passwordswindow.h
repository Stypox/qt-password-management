#ifndef PASSWORDSWINDOW_H
#define PASSWORDSWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "logindialog.h"
#include "src/res/settings.h"
#include "src/res/password.h"

namespace Ui {
class PasswordsWindow;
}

class PasswordsWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit PasswordsWindow(QWidget *parent = nullptr);
	~PasswordsWindow();

	void loadData();
	void saveData();

private:
	Ui::PasswordsWindow* ui;
	Settings m_settings;
	UserData m_userData;
	QVector<Password> m_passwords;
};

#endif // PASSWORDSWINDOW_H
