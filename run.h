#ifndef RUN_H
#define RUN_H

#include <QFile>
#include <QProcess>
#include <QDebug>
#include "parsejson.h"
#include "global.h"

struct Run{
    QString vbsPath;
    Run();
    ~Run(){}
    bool updateVbs();
    void go();    
};

#endif // RUN_H
