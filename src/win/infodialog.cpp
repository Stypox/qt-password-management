#include "infodialog.h"
#include "ui_infodialog.h"
#include "src/res/resources.h"

InfoDialog::InfoDialog(const QVector<Password> passwords, const Settings& settings, QWidget *parent) :
	QDialog{parent}, ui{new Ui::InfoDialog}, m_passwords{passwords}, m_settings{settings} {
	ui->setupUi(this);
#if OS_MOBILE
	setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif

	connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(close()));

	updateLabels();
	checkPwned();
}
InfoDialog::~InfoDialog() {
	delete ui;
}

void InfoDialog::updateLabels() {
	const QHash<QString, QString>& labels = res::infoLabels[m_settings.language];
	ui->pwnedTitle->setText(labels["pwnedTitle"]);
	ui->pwnedLoading->setText(labels["pwnedLoading"]);
	ui->helpTitle->setText(labels["helpTitle"]);
	ui->helpText->setText(labels["helpText"]);
	ui->infoTitle->setText(labels["infoTitle"]);
	ui->infoText->setText(labels["infoText"]);
}
void InfoDialog::checkPwned() {

}
