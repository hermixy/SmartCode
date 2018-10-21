#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T14:40:03
#
#-------------------------------------------------

QT       -= gui
QT       += xml

include(../../config.pri)

TARGET = makx
TEMPLATE = lib

DEFINES += MAKE_LIBRARY

SOURCES += \
    makefilegenerator.cpp

HEADERS +=\
        make_global.h \
    makefilegenerator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH+=  $$INCP/core\
               $$INCP/project\
               $$INCP/build


win32:LIBS+=  $$DESTDIR/libcore.a\
        $$DESTDIR/libprox.a\
        $$DESTDIR/libbldx.a
unix:LIBS=  $$DESTDIR/libqscintilla2.so \
        $$DESTDIR/libprox.so \
        $$DESTDIR/libtxted.so
