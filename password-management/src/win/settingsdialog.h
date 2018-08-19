#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QVector>
#include "src/res/settings.h"
#include "src/res/password.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit SettingsDialog(Settings& settings, UserData& userData, const QVector<Password>& passwords, QApplication& app, QWidget *parent = nullptr);
	~SettingsDialog();

private:
	void updateLabels();
	void setError(const QString& key);

private slots:
	void backup();
	void resetSettings();

	void ok();
	bool apply();

	void passwordChanged();
	void settingsChanged();

private:
	Ui::SettingsDialog *ui;
	QApplication& m_app;

	Settings& m_settings;
	UserData& m_userData;
	const QVector<Password>& m_passwords;

	bool m_settingsChanged;
};

#endif // SETTINGSDIALOG_H
