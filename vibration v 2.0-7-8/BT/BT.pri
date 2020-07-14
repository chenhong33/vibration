#-------------------------------------------------
#
# Project created by QtCreator 2020-05-08T16:46:15
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        $$PWD/bt.cpp \
    	$$PWD/brt901.cpp \
    $$PWD/fileconfigwindow.cpp

HEADERS += \
        $$PWD/bt.h \
    	$$PWD/bwtcommand.h \
    	$$PWD/brt901.h \
    $$PWD/fileconfigwindow.h

FORMS += \
        $$PWD/bt.ui \
    $$PWD/fileconfigwindow.ui
