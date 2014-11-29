#ifndef APPSETTINGS_H
#define APPSETTINGS_H
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>

class appSettings : public QSettings
{
    Q_OBJECT

public:
explicit appSettings(QObject *parent = 0) : QSettings(QSettings::UserScope, QCoreApplication::instance()->organizationName(), QCoreApplication::instance()->applicationName(), parent)
    {
        qDebug() << "Settings file is located at: " << fileName();
    }

    Q_INVOKABLE inline void setValue(const QString &key, const QVariant &value) {
        QSettings::setValue(key, value);
    }
    Q_INVOKABLE inline QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant()) const {
        return QSettings::value(key, defaultValue);
    }
};
Q_DECLARE_METATYPE(appSettings*)

#endif // APPSETTINGS_H
