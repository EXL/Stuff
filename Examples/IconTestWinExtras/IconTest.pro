#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T22:07:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IconTest
TEMPLATE = app

win32 {
    QT += winextras
}


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    IconTest.rc

RESOURCES += \
    IconTest.qrc
