#include "win/passwordswindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
	res::debug();

	QApplication app {argc, argv};
	PasswordsWindow passwordsWindow {};
	passwordsWindow.show();
	passwordsWindow.loadData();

	return app.exec();
}
