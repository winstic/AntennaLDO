#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QMap>

class global{
public:
    global();
    ~global(){}
    //void setSysParam(const QString &key, const QString &value);
    //QString getSysParam(const QString &key);
    static QStringList singleListRegularStr(QString str);
    static void registerParamter();
public:
    static QMap<QString, QString> sysParam;
};

#endif // GLOBAL_H
