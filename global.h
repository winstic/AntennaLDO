#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QMap>
#include <QFileInfo>
#include <QDir>

extern QMap<QString, QString> sysParam;
extern QMap<QString, QString> vbsVariables;

class global{
public:
    global();
    ~global(){}
    static QStringList singleListRegularStr(QString str);
    static QString getFileBySuffix(const QString &dir, const QString &suff);
    static void registerParamter();
    static QString getInfoFromRel(const QString &key);
    static QString getProjectName();
public:
};

#endif // GLOBAL_H
