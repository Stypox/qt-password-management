#ifndef PASSWORDSWINDOW_H
#define PASSWORDSWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <memory>
#include "src/res/settings.h"
#include "src/res/password.h"
#include "src/res/passwordwidget.h"

namespace Ui {
class PasswordsWindow;
}

class PasswordsWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit PasswordsWindow(QWidget *parent = nullptr);
	~PasswordsWindow();

	void loadData();

private:
	void saveData();
	void updateLabels();
	void updateColors();
	void updatePasswords();

private slots:
	void newPassword();
	void info();
	void settings();
	void logout();

	void addPassword(Password password);

	void editPassword(int index);
	void removePassword(int index);
	void changeItemSize(int index, QSize size);


private:
	Ui::PasswordsWindow* ui;

	Settings m_settings;
	UserData m_userData;
	QVector<Password> m_passwords;

	QVector<std::shared_ptr<PasswordWidget>> m_widgets;
};

#endif // PASSWORDSWINDOW_H
