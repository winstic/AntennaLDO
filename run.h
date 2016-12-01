#ifndef RUN_H
#define RUN_H

#include <QThread>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include "macrodefined.h"
#include "parsejson.h"
#include "global.h"

class ThreadRun : public QThread{
public:
    ThreadRun(ATNFLAG aflag);
    ~ThreadRun(){
        this->quit();
    }
    bool registerHfssVars();
    bool updateVbs(const QString vbsPath);
    QString M2GHz(QString mhz);

    //over write run function
    void run();
private:
    ATNFLAG atnflag;
    QString doDir;
    QString atnName;
    QMap<QString, QString> vbsVars;
    QJsonObject obj;
};

#endif // RUN_H
