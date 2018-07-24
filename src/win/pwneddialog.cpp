#include "pwneddialog.h"
#include "ui_pwneddialog.h"

PwnedDialog::PwnedDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PwnedDialog)
{
	ui->setupUi(this);
}

PwnedDialog::~PwnedDialog()
{
	delete ui;
}
