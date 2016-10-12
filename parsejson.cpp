#include "parsejson.h"

QJsonObject parseJson::getJsonObj(const QString &path){
    QJsonObject obj;
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(0, QString("Error"), QString("parseJson.cpp:7: error: Cannot read file %1").arg(path));
    }
    else{
        QByteArray byteArray = file.readAll();
        file.close();
        QJsonParseError jsonError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray, &jsonError);
        if(jsonError.error == QJsonParseError::NoError){
            if(jsonDocument.isObject()){
                obj = jsonDocument.object();
            }
        }
    }
    return obj;
}

QJsonObject parseJson::getSubJsonObj(const QJsonObject &obj, const QString &key){
    QJsonObject subObj;
    if(obj.contains(key)){
        QJsonValue value = obj.value(key);
        if(value.isObject())
            subObj = value.toObject();
    }
    return subObj;
}

bool parseJson::write(const QString &path, QJsonObject &obj){
    QFile file(path);
    if(!file.open(QFile::WriteOnly)){
        QMessageBox::critical(0, QString("Error"), QString("parseJson.cpp:36: error: Cannot read file %1").arg(path));
        return false;
    }
    QJsonDocument jsonDocument;
    jsonDocument.setObject(obj);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << QString(byteArray);
    file.close();
    return true;
}
