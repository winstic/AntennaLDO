#ifndef DESIGNRUN_H
#define DESIGNRUN_H

#include <QThread>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include "../Global/global.h"
#include "../Global/macrodefined.h"
#include "../Utility/parsejson.h"

class designRun : public QThread{
public:
    designRun();
    ~designRun(){
        this->quit();
    }
    bool registerHfssVars(const QJsonObject &obj);
    bool updateVbs(const QString &vbsPath);
    QString M2GHz(QString mhz);

    //over write run function
    void run();
private:
    //ATNFLAG atnflag;
    QString designDir;
    QString atnName;
    QMap<QString, QString> vbsVars;
};

#endif // RUN_H
