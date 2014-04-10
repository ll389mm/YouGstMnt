TARGET = Exec
DESTDIR = ../../lib/
VERSION = 1.0.0
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += ../Core/

LIBS += -L../../lib/    -lCore
QT       += core gui

