QT += xml

TARGET = Core
DESTDIR = ../../lib/
TEMPLATE = lib
CONFIG += thread shared warn_on release
VERSION = 1.0.0

INCLUDEPATH += \
    /usr/local/include

Release:LIBS += \
    /Users/poo/Desktop/opencv-2.4.8/build-lcxx/lib

Debug:LIBS += \
    /usr/local/lib

SOURCES += \
    label.cpp \
    implementationmanager.cpp \
    abstractmodel.cpp \
    classifier.cpp \
    labelmanager.cpp \
    classifiermanager.cpp \
    networkmanager.cpp \
    Features/colorspace.cpp \
    Features/cvgabor.cpp \
    Features/feature.cpp \
    Features/featuremanager.cpp \
    Features/featuretype.cpp \
    Features/LBP.cpp \
    Features/SPM.cpp \
    Models/MBRM.cpp \
    Models/model.cpp \
    Models/modeltype.cpp \
    Models/MyRealNo.cpp \
    Models/mysvm.cpp \
    Models/libsvm/svm.cpp \
    Models/libsvm/svm-predict.c \
    Models/libsvm/svm-scale.c \
    Models/libsvm/svm-train.c \
    Features/mbrmfeature.cpp \
    Models/modelmanager.cpp

HEADERS += \
    label.h \
    commondefinitions.h \
    implementationmanager.h \
    classifier.h \
    labelmanager.h \
    classifiermanager.h \
    networkmanager.h \
    Features/colorspace.h \
    Features/cvgabor.h \
    Features/feature.h \
    Features/featuremanager.h \
    Features/featuretype.h \
    Features/LBP.h \
    Features/SPM.h \
    Models/MBRM.h \
    Models/model.h \
    Models/modeltype.h \
    Models/MyRealNo.h \
    Models/mysvm.h \
    Models/libsvm/svm.h \
    Features/mbrmfeature.h \
    Models/modelmanager.h

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    Models/libsvm/svm.def
