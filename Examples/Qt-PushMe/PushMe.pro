#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T21:37:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PushMe
TEMPLATE = app


SOURCES += main.cpp\
        Widget.cpp

HEADERS  += Widget.h

FORMS    += Widget.ui

TRANSLATIONS += PushMe_en.ts \
            PushMe_ru.ts \
            PushMe_es.ts

RESOURCES += \
    PushMe.qrc
