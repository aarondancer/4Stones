#ifndef HTTPREQUESTWORKER_H
#define HTTPREQUESTWORKER_H

#include <QObject>

class HttpRequestWorker : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequestWorker(QObject *parent = 0);

signals:

public slots:

};

#endif // HTTPREQUESTWORKER_H
