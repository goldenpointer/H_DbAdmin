#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T16:30:58
#
#-------------------------------------------------

QT       += core gui network

RESOURCES     += resources/resources.qrc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = H_DbAdmin
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
        src/main.cpp \
        src/HttpAdapter.cpp \
        thirdparty/TreeItem.cpp \
        thirdparty/TreeModel.cpp \
    src/HDbAdminWindow.cpp

HEADERS += \
        src/HttpAdapter.h \
        thirdparty/TreeItem.h \
        thirdparty/TreeModel.h \
    src/HDbAdminWindow.h


FORMS += \
        forms/HDbAdmin.ui