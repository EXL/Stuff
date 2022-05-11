// g++ -fPIC -I/usr/include/x86_64-linux-gnu/qt5/ -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore qtgui.cpp -lQt5Core -lQt5Gui -lQt5Widgets

#include <QtGui>
#include <QtWidgets>
#include <QApplication>

int main(int c, char **v) { QApplication a(c, v); QPushButton b("HELLO"); b.show(); return a.exec(); }
