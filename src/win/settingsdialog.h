#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "src/res/settings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit SettingsDialog(Settings& settings, UserData& userData, QWidget *parent = nullptr);
	~SettingsDialog();

private:
	void updateLabels();

private slots:
	void backup();
	void resetSettings();

	void ok();
	void cancel();
	void apply();

private:
	Ui::SettingsDialog *ui;

	Settings& m_settings;
	UserData& m_userData;

	Settings m_settingsCopy;
	UserData m_userDataCopy;
};

#endif // SETTINGSDIALOG_H
