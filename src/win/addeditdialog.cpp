#include "addeditdialog.h"
#include "ui_addeditdialog.h"

AddEditDialog::AddEditDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddEditDialog)
{
	ui->setupUi(this);
}

AddEditDialog::~AddEditDialog()
{
	delete ui;
}
