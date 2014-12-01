TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    grid.cpp \
    player.cpp \
    global.cpp \
    ai.cpp \
    line.cpp \
    parsehelper.cpp \
    settings.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    grid.h \
    player.h \
    global.h \
    ai.h \
    line.h \
    parsehelper.h \
    settings.h

LIBS += -L$$[QT_INSTALL_LIBS]/../qml/QtQuick.2/
QTPLUGIN += QtQuick2Plugin

CONFIG += c++11

ICON = 4Stones.icns

RC_FILE = 4Stones.rc
