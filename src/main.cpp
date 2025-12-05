#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <sodium.h>

int main(int argc, char *argv[])
{
    if (sodium_init() < 0) {
        qFatal("Libsodium failed to initialize");
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTimer::singleShot(0, &w, &MainWindow::startLoginFlow);
    return a.exec();
}
