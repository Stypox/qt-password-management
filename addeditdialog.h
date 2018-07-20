#ifndef ADDEDITDIALOG_H
#define ADDEDITDIALOG_H

#include <QDialog>

namespace Ui {
class AddEditDialog;
}

class AddEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditDialog(QWidget *parent = 0);
    ~AddEditDialog();

private:
    Ui::AddEditDialog *ui;
};

#endif // ADDEDITDIALOG_H
