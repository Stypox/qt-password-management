#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QVector>
#include "settings.h"
#include "password.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(Settings& settings, QVector<Password>& passwords, QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    Settings& m_settings;
    QVector<Password>& m_passwords;
};

#endif // LOGINDIALOG_H
