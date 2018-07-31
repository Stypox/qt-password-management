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
	explicit SettingsDialog(Settings& settings, UserData& userData, const QVector<Password>& passwords, QWidget *parent = nullptr);
	~SettingsDialog();

private:
	void updateLabels();
	void setError(const QString& key);

private slots:
	void backup();
	void resetSettings();

	void ok();
	void apply();

	void passwordChanged();
	void disableBackup();

private:
	Ui::SettingsDialog *ui;

	Settings& m_settings;
	UserData& m_userData;
	const QVector<Password>& m_passwords;
};

#endif // SETTINGSDIALOG_H
