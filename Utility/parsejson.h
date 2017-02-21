#ifndef PARSEJSON_H
#define PARSEJSON_H

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QJsonParseError>
#include <QString>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class parseJson{
public:
    parseJson(){}
    ~parseJson(){}
public:
    static QJsonObject getJsonObj(const QString &path);
    static QJsonObject getSubJsonObj(const QJsonObject &obj, const QString &key);
    static bool write(const QString &path, QJsonObject &obj);
};

#endif // PARSEJSON_H
