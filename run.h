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
    void go();
    QString M2GHz(QString mhz);
private:
    QString vbsPath;
    QMap<QString, QString> vbsVars;
    QJsonObject obj;
};

#endif // RUN_H
