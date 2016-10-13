#ifndef RUN_H
#define RUN_H

#include <QFile>
#include <QProcess>
#include <QDebug>
#include "parsejson.h"
#include "global.h"

class Run{
public:
    Run();
    ~Run(){}
    bool registerHfssVars();
    bool updateVbs();
    bool go();
    QString M2GHz(QString mhz);
private:
    QString designDir;
    QString vbsPath;
    QString atnName;
    QMap<QString, QString> vbsVars;
    QJsonObject obj;
};

#endif // RUN_H
