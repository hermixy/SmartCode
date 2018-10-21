#-------------------------------------------------
#
# Project created by QtCreator 2015-02-27T22:34:59
#
#-------------------------------------------------

QT       += widgets xml

TARGET = designer
TEMPLATE = lib

DEFINES += DESIGNER_LIBRARY

SOURCES += designer.cpp

HEADERS += designer.h\
        designer_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
