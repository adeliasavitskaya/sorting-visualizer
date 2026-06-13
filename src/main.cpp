#include <QApplication>
#include "ui/app_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    AppWindow window;
    window.show();
    return app.exec();
}