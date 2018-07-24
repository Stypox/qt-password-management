#include "win/passwordswindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	res::debug();

	QApplication app {argc, argv};
	PasswordsWindow passwordsWindow {};
	passwordsWindow.show();

	return app.exec();
}
