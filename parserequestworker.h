#ifndef ParseRequestWORKER_H
#define ParseRequestWORKER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

enum ParseRequestVarLayout {NOT_SET, ADDRESS, URL_ENCODED, MULTIPART};

class ParseRequestInputFileElement {

public:
    QString variable_name;
    QString local_filename;
    QString request_filename;
    QString mime_type;

};

class ParseRequestInput {

public:
    QString url_str;
    QString http_method;
    ParseRequestVarLayout var_layout;
    QMap<QString, QString> vars;
    QList<ParseRequestInputFileElement> files;

    ParseRequestInput();
    ParseRequestInput(QString v_url_str, QString v_http_method);
    void initialize();
    void add_var(QString key, QString value);
    void add_file(QString variable_name, QString local_filename, QString request_filename, QString mime_type);

};

class ParseRequestWorker : public QObject {
    Q_OBJECT

public:
    QByteArray response;
    QNetworkReply::NetworkError error_type;
    QString error_str;

    explicit ParseRequestWorker(QObject *parent = 0);

    QString http_attribute_encode(QString attribute_name, QString input);
    void execute(ParseRequestInput *input);

signals:
    void on_execution_finished(ParseRequestWorker *worker);

private:
    QNetworkAccessManager *manager;

private slots:
    void on_manager_finished(QNetworkReply *reply);

};

#endif // ParseRequestWORKER_H
