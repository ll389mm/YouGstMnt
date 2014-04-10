QT       += core gui widgets

TARGET = QtGUI
DESTDIR = ../../lib/
TEMPLATE = lib
CONFIG += qt shared thread warn_on release
VERSION = 1.0.0

INCLUDEPATH += ../Core/

LIBS += -L../../lib/    -lCore


HEADERS += \
    newlabeldialog.h \
    newclassifierdialog.h \
    maindialog.h \
    traindialog.h \
    utilities.h \
    editlabeldialog.h

SOURCES += \
    newlabeldialog.cpp \
    newclassifierdialog.cpp \
    maindialog.cpp \
    traindialog.cpp \
    utilities.cpp \
    editlabeldialog.cpp

FORMS += \
    newlabeldialog.ui \
    newclassifierdialog.ui \
    maindialog.ui \
    traindialog.ui \
    editlabeldialog.ui
