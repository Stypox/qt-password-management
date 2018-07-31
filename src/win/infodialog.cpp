#include "infodialog.h"
#include "ui_infodialog.h"
#include "src/res/resources.h"

InfoDialog::InfoDialog(QWidget *parent) :
	QDialog(parent), ui(new Ui::InfoDialog) {
	ui->setupUi(this);
#if OS_MOBILE
	setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
#endif

	connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(close()));
}

InfoDialog::~InfoDialog() {
	delete ui;
}
