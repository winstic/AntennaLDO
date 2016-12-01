#ifndef RUN_H
#define RUN_H

#include <QThread>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include "parsejson.h"
#include "global.h"

class ThreadRun : public QThread{
public:
    ThreadRun();
    ~ThreadRun(){
        this->quit();
    }
    bool registerHfssVars();
    bool updateVbs();
    QString M2GHz(QString mhz);

    //over write run function
    void run();
private:
    QString designDir;
    QString vbsPath;
    QString atnName;
    QMap<QString, QString> vbsVars;
    QJsonObject obj;
};

#endif // RUN_H
