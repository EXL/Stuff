#include "networkmanagerdemowidget.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    NetworkManagerDemoWidget w;
    w.show();
    return a.exec();
}
