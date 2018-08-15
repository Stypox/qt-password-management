#include "passwordwidget.h"
#include <QDebug>

PasswordWidget::PasswordWidget(const int& index, Password& password, const Settings& settings, QWidget* parent, const bool& opened) :
	QWidget{parent}, m_index{index}, m_password{password},
	m_settings(settings), m_opened(opened),
	m_closedLay{new QHBoxLayout{}}, m_openBut{new QToolButton{}},
	m_closedNameLab{new QLabel{}},
	m_openedLay{new QHBoxLayout{}}, m_labelsLay{new QFormLayout{}},
	m_buttonsLay{new QVBoxLayout{}},
	m_closeBut{new QToolButton{}}, m_editBut{new QToolButton{}},
	m_removeBut{new QToolButton{}},
	m_passwordTitle{new QLabel{}}, m_emailTitle{new QLabel{}},
	m_usernameTitle{new QLabel{}},
	m_openedNameLab{new QLabel{}}, m_passwordLab{new QLabel{}},
	m_emailLab{new QLabel{}}, m_usernameLab{new QLabel{}},
	m_descriptionLab{new QTextBrowser{}},
	swapOpen{}, swapClose{}
{
	connect(m_openBut, SIGNAL(clicked(bool)), this, SLOT(setOpened()));
	connect(m_closeBut, SIGNAL(clicked(bool)), this, SLOT(setClosed()));
	connect(m_editBut, SIGNAL(clicked(bool)), this, SLOT(toEdit()));
	connect(m_removeBut, SIGNAL(clicked(bool)), this, SLOT(toRemove()));
	connect(this, SIGNAL(edit(int)), parent, SLOT(editPassword(int)));
	connect(this, SIGNAL(remove(int)), parent, SLOT(removePassword(int)));

	updateLabels();
	buildClosedLay();
	buildOpenedLay();
	if (m_opened)
		setOpened();
	else
		setClosed();

	connect(this, SIGNAL(sizeChanged(int, QSize)), parent, SLOT(changeItemSize(int, QSize)));
}
PasswordWidget::~PasswordWidget() {
	delete m_closedLay;
	delete m_openBut;
	delete m_closedNameLab;

	delete m_openedLay;

	delete m_closeBut;
	delete m_editBut;
	delete m_removeBut;

	delete m_passwordTitle;
	delete m_emailTitle;
	delete m_usernameTitle;

	delete m_openedNameLab;
	delete m_passwordLab;
	delete m_emailLab;
	delete m_usernameLab;
	delete m_descriptionLab;
}

constexpr int PasswordWidget::getHeight(const bool& opened) {
	return opened ? res::passwordWidgetOpenedHeight : res::passwordWidgetClosedHeight;
}
int PasswordWidget::getHeight() const {
	return m_opened ? res::passwordWidgetOpenedHeight : res::passwordWidgetClosedHeight;
}
bool PasswordWidget::isOpened() const {
	return m_opened;
}

void PasswordWidget::setIndex(const int& index) {
	m_index = index;
}

void PasswordWidget::updateLabels() {
#if !OS_MOBILE
	m_openBut->setArrowType(Qt::ArrowType::LeftArrow);
	m_closeBut->setArrowType(Qt::ArrowType::DownArrow);
#endif
	m_openedNameLab->setAlignment(Qt::AlignCenter);
	m_openBut->setAutoRaise(true);
	m_closeBut->setAutoRaise(true);
	m_editBut->setAutoRaise(true);
	m_removeBut->setAutoRaise(true);

	QFont bold {m_openedNameLab->font()};
	bold.setBold(true);
	m_openedNameLab->setFont(bold);
	m_passwordLab->setFont(bold);
	m_emailLab->setFont(bold);
	m_usernameLab->setFont(bold);

	m_openBut->setFont(res::iconFont);
	m_closeBut->setFont(res::iconFont);
	m_editBut->setFont(res::iconFont);
	m_removeBut->setFont(res::iconFont);

	m_openBut->setText(QString{QChar{0x25C0}});
	m_closeBut->setText(QString{QChar{0x25BC}});
	m_editBut->setText(QString{QChar{0x270D/*270E*/}});
	m_removeBut->setText(QString{QChar{0x00D7}});

	m_passwordTitle->setText(res::widgetLabels[m_settings.language]["passwordTitle"]);
	m_emailTitle->setText(res::widgetLabels[m_settings.language]["emailTitle"]);
	m_usernameTitle->setText(res::widgetLabels[m_settings.language]["usernameTitle"]);

	m_closedNameLab->setText(m_password.name);
	m_openedNameLab->setText(m_password.name);
	m_passwordLab->setText(m_password.password);
	m_emailLab->setText(m_password.email);
	m_usernameLab->setText(m_password.username);
	m_descriptionLab->setText(m_password.description);

}

void PasswordWidget::buildClosedLay() {
	m_closedLay->addWidget(m_closedNameLab);
	m_closedLay->addWidget(m_openBut);

	m_closedLay->update();
}
void PasswordWidget::buildOpenedLay() {
	m_labelsLay->addRow(m_openedNameLab);
	m_labelsLay->addRow(m_passwordTitle, m_passwordLab);
	m_labelsLay->addRow(m_emailTitle, m_emailLab);
	m_labelsLay->addRow(m_usernameTitle, m_usernameLab);
	m_labelsLay->addRow(m_descriptionLab);

	m_buttonsLay->addWidget(m_closeBut, 0, Qt::AlignCenter);
	m_buttonsLay->addWidget(m_editBut, 0, Qt::AlignCenter);
	m_buttonsLay->addWidget(m_removeBut, 0, Qt::AlignCenter);

	m_openedLay->addItem(m_labelsLay);
	m_openedLay->addItem(m_buttonsLay);

	m_openedLay->update();
}

void PasswordWidget::toEdit() {
	edit(m_index);
	updateLabels();
}
void PasswordWidget::toRemove() {
	remove(m_index);
}

void PasswordWidget::setClosed() {
	m_opened = false;
	swapOpen.setLayout(m_openedLay);
	setLayout(m_closedLay);
	sizeChanged(m_index, QSize{0, res::passwordWidgetClosedHeight});
}
void PasswordWidget::setOpened() {
	m_opened = true;
	swapClose.setLayout(m_closedLay);
	setLayout(m_openedLay);
	sizeChanged(m_index, QSize{0, res::passwordWidgetOpenedHeight});
}
