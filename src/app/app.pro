#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T17:18:50
#
#-------------------------------------------------


QT += core gui xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCode
TEMPLATE = app

CONFIG += create_prl

include(../../config.pri)

SOURCES += main.cpp \
    mainwindow.cpp \
    options.cpp

HEADERS  += \
    mainwindow.h \
    options.h

RC_FILE = smart.rc

FORMS    += mainwindow.ui \
    About.ui \
    options.ui

RESOURCES += \
    resource.qrc

INCLUDEPATH+=   \
                $$INCP/core \
                $$INCP/libs/qscintilla/Qt4Qt5 \
                $$INCP/texteditor \
                $$INCP/project \
                $$INCP/build \
                $$INCP/search \
                $$INCP/compability \
                $$INCP/make

win32:LIBS+=  $$DESTDIR/libcore.a \
        $$DESTDIR/libqscintilla2.a \
        $$DESTDIR/libtxted.a \
        $$DESTDIR/libprox.a \
        $$DESTDIR/libbldx.a \
        $$DESTDIR/libsearch.a \
        $$DESTDIR/libcompb.a \
        $$DESTDIR/libmakx.a
unix:LIBS+=  $$DESTDIR/libcore.so \
        $$DESTDIR/libqscintilla2.so \
        $$DESTDIR/libtxted.so \
        $$DESTDIR/libprox.so \
        $$DESTDIR/libbldx.so \
        $$DESTDIR/libsearch.so \
        $$DESTDIR/libcompb.so \
        $$DESTDIR/libmakx.so \
        $$DESTDIR/libvercontr.so \
        $$DESTDIR/libastyle.so
OTHER_FILES += \
    ../../config.pri

ICON = myapp.icns




