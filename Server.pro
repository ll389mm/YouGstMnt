TEMPLATE = subdirs
CONFIG += warn_on release thread
VERSION = 1.0.0

SUBDIRS += \
    App \
    Core \
    QtGUI \
    Executable


App.depends += Core
QtGUI.depends += Core
UnitTest.depends += Core
BasicImpl.depends += Core
