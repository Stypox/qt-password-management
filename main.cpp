#include "src/win/passwordswindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app {argc, argv};
    PasswordsWindow passwordsWindow {};
    passwordsWindow.show();

    return app.exec();
}
