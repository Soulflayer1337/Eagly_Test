#include <QCoreApplication>
#include <QTimer>
#include "dialog/dialog.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dialog *dialog = new Dialog(a.applicationDirPath(), &a);
    QObject::connect(dialog, SIGNAL(quit()), &a, SLOT(quit()));
    QTimer::singleShot(0, dialog, SLOT(setSwitcher()));
    QTimer *timer = new QTimer(&a);
    QObject::connect(timer, SIGNAL(timeout()), dialog, SLOT(startDialog()));
    timer->start(2000);

    return a.exec();
}
