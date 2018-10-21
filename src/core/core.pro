#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T16:04:44
#
#-------------------------------------------------

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

include(../../config.pri)

DEFINES += CORE_LIBRARY

SOURCES += \
    autosave.cpp \
    dialog.cpp \
    recents.cpp \
    startpage.cpp \
    tabsetting.cpp \
    bases.cpp \
    settingsdocument.cpp \
    tabsettingmanager.cpp \
    host.cpp \
    environment.cpp \
    buildvariables.cpp \
    variables.cpp \
    filemanager.cpp

HEADERS +=\
        core_global.h \
    core_constants.h \
    autosave.h \
    dialog.h \
    recents.h \
    startpage.h \
    tabsetting.h \
    bases.h \
    settingsdocument.h \
    tabsettingmanager.h \
    host.h \
    environment.h \
    buildvariables.h \
    variables.h \
    filemanager.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE128486C
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = core.dll
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

RESOURCES += \
    resource.qrc

FORMS += \
    startpage.ui \
    tabsetting.ui \
    startProjects.ui
