#ifndef PWNEDDIALOG_H
#define PWNEDDIALOG_H

#include <QDialog>

namespace Ui {
class PwnedDialog;
}

class PwnedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PwnedDialog(QWidget *parent = 0);
    ~PwnedDialog();

private:
    Ui::PwnedDialog *ui;
};

#endif // PWNEDDIALOG_H
