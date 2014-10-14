#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QDebug>
//#include "grid.h"
#include <stdlib.h>
//#include <iostream>
#include <QtQml>
#include <QObject>
#include "ai.h"
#include "player.h"
#include <QQuickView>
#include <QQuickItem>

QList<Player*> players;

void createOpponent(int difficulty);

int main(int argc, char *argv[])
{
    createOpponent(0);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Grid>("com.FourStones.qmlcomponents", 1, 0, "Grid"); //Register the Grid class as a type that can be used in QML

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));

    QQuickWindow *W = (QQuickWindow *)engine.rootObjects().first();
    Grid *board = W->findChild<Grid*>("boardo");


    //if (G) qDebug() << "woo!";

//    QQmlEngine e;
//    QQmlComponent component(&e, QUrl("qrc:/main.qml"));
//    QObject *object = component.create();
//    Grid *board = object->findChild<Grid*>("boardo");

//    qDebug() << component.errors();




    return app.exec();

}

void createOpponent(int difficulty){
    switch(difficulty){
        Player* temp;
        case 0:
            temp = new Player();
            players.append(temp);
            break;
        case 1:
            temp = new AI() ;
            players.append(temp);
            break;
        case 2:
            temp = new AI() ;
            players.append(temp);
            break;
        case 3:
            temp = new AI() ;
            players.append(temp);
            break;
        default: break;

    }
}
