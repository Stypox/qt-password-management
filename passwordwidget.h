#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H
#include <QObject>
#include <QWidget>
#include "passwordstructure.h"


class PasswordWidget : public QWidget {
    Q_OBJECT
public:
    PasswordWidget(int listIndex, PasswordStructure password);

private slots:
    void setLittle();
    void setBig();

signals:
    void edit(int listIndex);

private:
    int m_listIndex;
    PasswordStructure m_password;
};

#endif // PASSWORDWIDGET_H
