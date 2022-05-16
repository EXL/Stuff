#include "TimeDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimeDialog w;
    w.show();

    return a.exec();
}
