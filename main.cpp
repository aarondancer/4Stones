#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
//#include <QDebug>
#include "grid.h"
#include <stdlib.h>
//#include <iostream>
#include <QtQml>
#include <QObject>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Grid>("com.FourStones.qmlcomponents", 1, 0, "Grid"); //Register the Grid class as a type that can be used in QML

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//    Grid grid;
//    engine.rootContext()->setContextProperty("Grid", &grid);
//    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
//    component.create();

    return app.exec();

}
