#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H
#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QToolButton>
#include <QLabel>
#include <QTextBrowser>
#include "password.h"
#include "resources.h"
#include "settings.h"

class PasswordWidget : public QWidget {
	Q_OBJECT
public:
	PasswordWidget(const int& index, const Password* password, const Settings& settings, QWidget* parent, const bool& opened = false);
	~PasswordWidget();

	static constexpr int getHeight(const bool& opened);
	int getHeight() const;
	bool isOpened() const;

	void setIndex(const int& index);
	void setPassword(const Password* m_password, bool update = true);

private:
	void updateLabels();

	void buildClosedLay();
	void buildOpenedLay();

private slots:
	void toEdit();
	void toRemove();

	void setClosed();
	void setOpened();

signals:
	void edit(int index);
	void remove(int index);
	void sizeChanged(int index, QSize item);

private:
	int m_index;
	const Password* m_password;
	const Settings& m_settings;
	bool m_opened;

	QHBoxLayout* m_closedLay;
	QToolButton* m_openBut;
	QLabel* m_closedNameLab;

	QHBoxLayout* m_openedLay;
	QFormLayout* m_labelsLay;
	QVBoxLayout* m_buttonsLay;

	QToolButton* m_closeBut;
	QToolButton* m_editBut;
	QToolButton* m_removeBut;

	QLabel* m_passwordTitle;
	QLabel* m_emailTitle;
	QLabel* m_usernameTitle;

	QLabel* m_openedNameLab;
	QLabel* m_passwordLab;
	QLabel* m_emailLab;
	QLabel* m_usernameLab;
	QTextBrowser* m_descriptionLab;

	QWidget swapOpen, swapClose;
};

#endif // PASSWORDWIDGET_H
