TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

D_IN = $$PWD/task.in
D_OUT = $$OUT_PWD

win32: {
    D_IN ~= s,/,\\,g
    D_OUT ~= s,/,\\,g
}

deploy.commands = $(COPY_DIR) $$D_IN $$D_OUT
first.depends = $(first) deploy
export(first.depends)
export(deploy.commands)
QMAKE_EXTRA_TARGETS += first deploy

HEADERS += Iterator.h

SOURCES += main.cpp
