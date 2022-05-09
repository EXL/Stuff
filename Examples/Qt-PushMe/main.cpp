#include "Widget.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(time(0));

    QTranslator appTranslator;
    appTranslator.load("PushMe_" + QLocale::system().name(), "://");
    a.installTranslator(&appTranslator);

    Widget w;
    w.show();

    return a.exec();
}
