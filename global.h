#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QMap>
#include <QFileInfo>
#include <QDir>

extern QMap<QString, QString> sysParam;

class global{
public:
    global();
    ~global(){}
    static QStringList str2list(QString str);
    static QString str2liststr(const QString &str);
    static QString getFileBySuffix(const QString &dir, const QString &suff);
    static void registerParamter();
    static QString getInfoFromRel(const QString &key);
    static QString getProjectName();
public:
};

#endif // GLOBAL_H
