QT       += core gui network opengl sql webkit xml xmlpatterns testlib

TARGET = tst_unittesttest
DESTDIR = ../../bin/
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Core/

LIBS += -L../../lib/ -lCore


SOURCES += tst_unittesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
