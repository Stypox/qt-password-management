#ifndef PASSWORDSWINDOW_H
#define PASSWORDSWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QModelIndexList>
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
	explicit PasswordsWindow(QApplication& app, QWidget *parent = nullptr);
	~PasswordsWindow();

	void loadData();

private:
	void saveData();

	void updateReorderingActive();
	void updateLabels();
	void updateColors();
	void updatePasswords();

private slots:
	void newPassword();
	void info();
	void settings();
	void logout();

	void addPassword(Password password);

	void movePasswords(const QModelIndex&, int from, int, const QModelIndex&, int to);
	void editPassword(int index);
	void removePassword(int index);
	void changeItemSize(int index, QSize size);


private:
	Ui::PasswordsWindow* ui;
	QApplication& m_app;

	Settings m_settings;
	UserData m_userData;
	QVector<Password> m_passwords;

	QVector<std::shared_ptr<PasswordWidget>> m_widgets;
};

#endif // PASSWORDSWINDOW_H
