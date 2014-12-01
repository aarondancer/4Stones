#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

class settings : public QObject
{
    Q_OBJECT
public:
    explicit settings(QObject *parent = 0);
    ~settings();
    QSettings* q;

    Q_INVOKABLE void setValue(QString key, QVariant value) {
        q->setValue(key, value);
    }
    Q_INVOKABLE QVariant getValue(QString key, QVariant value) {
        return q->value(key, value);
    }

signals:

public slots:

};

#endif // SETTINGS_H
