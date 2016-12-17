#ifndef OPTIMIZERUN_H
#define OPTIMIZERUN_H

#include <QThread>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include "global.h"
#include "parsejson.h"
#include "sqliteManage.h"

class optimizeRun : public QThread{
public:
    optimizeRun();
    ~optimizeRun(){
        this->quit();
    }

protected:
    void run();

private:
    //include problem,algorithm,global configure infomation
    void setInfo();
    bool update2DEA4AD();

    QString optimizeDir;
    QString DEA4ADPath;
    QString atnName;
    QString atnPath;
    QString algorithmName;
    QString algorithmPath;
};

#endif // OPTIMIZERUN_H
