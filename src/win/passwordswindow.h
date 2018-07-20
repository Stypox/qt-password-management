#ifndef PASSWORDSWINDOW_H
#define PASSWORDSWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "logindialog.h"
#include "settings.h"
#include "password.h"

namespace Ui {
class PasswordsWindow;
}

class PasswordsWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit PasswordsWindow(QWidget *parent = 0);
    ~PasswordsWindow();

private:
    Ui::PasswordsWindow* ui;
    Settings m_settings;
    QVector<Password> m_passwords;
};

#endif // PASSWORDSWINDOW_H
