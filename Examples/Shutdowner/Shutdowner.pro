#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T22:35:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

D_IN = $$PWD/config.ini
D_OUT = $$OUT_PWD

win32: {
    D_IN ~= s,/,\\,g
    D_OUT ~= s,/,\\,g
}

deploy.commands = $$QMAKE_COPY $$D_IN $$D_OUT
first.depends = $(first) deploy
export(first.depends)
export(deploy.commands)
QMAKE_EXTRA_TARGETS += first deploy

unix: {
    QT += x11extras
}

TARGET = Shutdowner
TEMPLATE = app

SOURCES += main.cpp\
        Dialog.cpp \
    LCDNumber.cpp

HEADERS  += Dialog.h \
    LCDNumber.h

FORMS    += Dialog.ui

unix: {
    LIBS += -lX11
}

win: {
    QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
}
