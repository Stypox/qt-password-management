#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>

#include "win/passwordswindow.h"

#include "res/resources_init.cpp"

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
	res::darkTheme.load();
	res::debug();

	QApplication app{argc, argv};
	qDebug() << app.styleSheet();

	PasswordsWindow passwordsWindow {app};
	passwordsWindow.show();
	passwordsWindow.loadData();

	return app.exec();
}
