#-------------------------------------------------
#
# Project created by QtCreator 2014-03-13T18:25:28
#
#-------------------------------------------------

QT       += xml

TARGET = compb

TEMPLATE = lib

include(../../config.pri)
DEFINES += COMPABILITY_LIBRARY

SOURCES += \
    project/devcpp.cpp \
    project/codeblocks.cpp \
    qtapp.cpp

HEADERS +=\
        compability_global.h \
    project/devcpp.h \
    project/codeblocks.h \
    qtapp.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE25D1CD6
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = compability.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
INCLUDEPATH+= . $$INCP/project\
                $$INCP/core

win32:LIBS+=$$DESTDIR/libprox.a \
      $$DESTDIR/libcore.a

unix:LIBS+=$$DESTDIR/libprox.so \
      $$DESTDIR/libcore.so
