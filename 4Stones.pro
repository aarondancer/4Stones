TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    grid.cpp \
    player.cpp \
    ai.cpp \
    global.cpp \
    mediumai.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    grid.h \
    player.h \
    ai.h \
    global.h \
    mediumai.h

LIBS += -L$$[QT_INSTALL_LIBS]/../qml/QtQuick.2/
QTPLUGIN += QtQuick2Plugin
