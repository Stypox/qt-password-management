#ifndef ADDEDITDIALOG_H
#define ADDEDITDIALOG_H

#include <QDialog>
#include <QVector>
#include "src/res/password.h"
#include "src/res/settings.h"

namespace Ui {
class AddEditDialog;
}

class AddEditDialog : public QDialog {
	Q_OBJECT

public:
	explicit AddEditDialog(Settings& settings, QWidget* parent);								//add mode
	explicit AddEditDialog(Password* password, Settings& settings, QWidget* parent = nullptr);	//edit mode
	~AddEditDialog();

private:
	void updateLabels();

private slots:
	void ok();
	void cancel();

signals:
	void addPassword(Password password);

private:
	Ui::AddEditDialog *ui;
	const bool m_edit;
	Password* m_password;
	Settings& m_settings;
};

#endif // ADDEDITDIALOG_H
