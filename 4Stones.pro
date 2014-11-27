TEMPLATE = app

QT += qml quick \
    widgets

SOURCES += main.cpp \
    grid.cpp \
    player.cpp \
    global.cpp \
    ai.cpp \
    parserequestworker.cpp \
    line.cpp

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
    parserequestworker.h \
    line.h

LIBS += -L$$[QT_INSTALL_LIBS]/../qml/QtQuick.2/
QTPLUGIN += QtQuick2Plugin

CONFIG += c++11
