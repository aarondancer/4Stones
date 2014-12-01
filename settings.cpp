#include "settings.h"
#include <QDebug>

settings::settings(QObject *parent) :
    QObject(parent)
{
    q = new QSettings(QCoreApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);
}

settings::~settings()
{
    delete q;
}
