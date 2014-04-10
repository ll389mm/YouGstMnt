TARGET = Server
DESTDIR = ../../bin/
TEMPLATE = app
CONFIG += console qt thread release warn_on
VERSION = 1.0.0

INCLUDEPATH += ../Core/    ../QtGUI/

LIBS += -L../../lib/    -lCore    -lQtGUI

QT += core gui widgets

SOURCES += \
    main.cpp
