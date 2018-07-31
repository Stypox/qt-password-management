#include "addeditdialog.h"
#include "ui_addeditdialog.h"
#include "src/res/resources.h"
#include <QDebug>

AddEditDialog::AddEditDialog(Settings& settings, QWidget* parent) :
	AddEditDialog{nullptr, settings, parent} {}
AddEditDialog::AddEditDialog(Password* password, Settings& settings, QWidget *parent) :
	QDialog(parent), ui(new Ui::AddEditDialog), m_edit{password != nullptr}, m_password{password}, m_settings{settings} {
	ui->setupUi(this);
	setInputMethodHints(res::inputMethod);
#if OS_MOBILE
	setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif

	updateLabels();
	if (m_edit) {
		ui->nameEditor->setText(m_password->name);
		ui->passwordEditor->setText(m_password->password);
		ui->emailEditor->setText(m_password->email);
		ui->usernameEditor->setText(m_password->username);
		ui->descriptionEditor->insertPlainText(m_password->description);
	}

	connect(this, SIGNAL(addPassword(Password)), parent, SLOT(addPassword(Password)));
	connect(ui->ok, SIGNAL(clicked(bool)), this, SLOT(ok()));
	connect(ui->cancel, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}
AddEditDialog::~AddEditDialog() {
	delete ui;
}

void AddEditDialog::updateLabels() {
	const QHash<QString, QString>& labels {res::addEditLabels[m_settings.language]};
	if (m_edit)
		ui->title->setText(labels["editPassword"].arg(m_password->name));
	else
		ui->title->setText(labels["newPassword"]);
	ui->nameTitle->setText(labels["nameTitle"]);
	ui->passwordTitle->setText(labels["passwordTitle"]);
	ui->emailTitle->setText(labels["emailTitle"]);
	ui->usernameTitle->setText(labels["usernameTitle"]);
}

void AddEditDialog::ok() {
	if (m_edit) {
		m_password->name = ui->nameEditor->text();
		m_password->password = ui->passwordEditor->text();
		m_password->email = ui->emailEditor->text();
		m_password->username = ui->usernameEditor->text();
		m_password->description = ui->descriptionEditor->toPlainText();
	}
	else {
		addPassword({ui->nameEditor->text(),
					ui->passwordEditor->text(),
					ui->emailEditor->text(),
					ui->usernameEditor->text(),
					ui->descriptionEditor->toPlainText()});
	}

	close();
}
void AddEditDialog::cancel() {
	close();
}
