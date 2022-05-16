#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T08:00:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtime
TEMPLATE = app


SOURCES += main.cpp\
        TimeDialog.cpp \
    TimeTableModel.cpp

HEADERS  += TimeDialog.h \
    TimeTableModel.h

FORMS    += TimeDialog.ui
