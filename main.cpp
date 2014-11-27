#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "grid.h"
#include "global.h"
//#include <stdlib.h>
//#include <iostream>
#include <QtQml>
#include "ai.h"
#include "player.h"
#include <QQuickView>

//Player* player;
//AI* computer;

int main(int argc, char *argv[])
{
    //createOpponent(0);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Grid>("com.FourStones.qmlcomponents", 1, 0, "Grid"); //Register the Grid class as a type that can be used in QML
    qmlRegisterType<Player>("com.FourStones.qmlcomponents", 1, 0, "Player");
    qmlRegisterType<AI>("com.FourStones.qmlcomponents", 1, 0, "AI");

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));

    QQuickWindow *W = (QQuickWindow *)engine.rootObjects().first();
    board = W->findChild<Grid*>("boardo");
//    player = W->findChild<Player*>("playero");
//    computer = W->findChild<AI*>("aio");

    return app.exec();

}
