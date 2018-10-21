

QT += core gui xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCode
TEMPLATE = app

CONFIG += create_prl

include(../../config.pri)

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS  += \
    mainwindow.h

FORMS    += mainwindow.ui \

INCLUDEPATH+=   \
                $$INCP/core \
                $$INCP/libs/qscintilla/Qt4Qt5 \
                $$INCP/texteditor \

LIBS+=  $$DESTDIR/libcore.a \
        $$DESTDIR/libqscintilla2.a \
        $$DESTDIR/libtxted.a

OTHER_FILES += \
    ../../config.pri



