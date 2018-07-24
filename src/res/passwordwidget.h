#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H
#include <QObject>
#include <QWidget>
#include "password.h"


class PasswordWidget : public QWidget {
	Q_OBJECT
public:
	PasswordWidget(const int& listIndex, Password& password);

private slots:
	void setLittle();
	void setBig();

signals:
	void edit(const int& listIndex);

private:
	int m_listIndex;
	Password& m_password;
};

#endif // PASSWORDWIDGET_H
