#include "win/passwordswindow.h"
#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>

res::Config res::config{};

int main(int argc, char *argv[]) {
	QLoggingCategory::setFilterRules("*.debug=true\n"
									 "qt.qpa.input*.debug=false\n"
									 "qt.widgets.gestures.debug=false\n"
									 "qt.widgets.gestures.info=false\n"
									 "qt.widgets.gestures.warning=false\n"
									 "qt.qpa.xkeyboard.debug=false\n"
									 "qt.qpa.gl.debug=false\n"
									 "qt.qpa.xcb.debug=false\n"
									 "qt.qpa.screen.debug=false\n"
									 "qt.scaling.debug=false\n"
									 );
	res::debug();

	QApplication app {argc, argv};
	PasswordsWindow passwordsWindow {};
	passwordsWindow.show();
	passwordsWindow.loadData();

	return app.exec();
}
