#include "zentrywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ZentryWindow w;
    w.show();
    return a.exec();
}
