#include "global.h"

QMap<QString, QString> global::sysParam;

global::global(){
    //sysParam["ProjectPath"] = "";
    //sysParam["WorkingPath"] = "";
    //sysParam["ModelVariables"] = "";
    //sysParam["ModelFile"] = "";
    //sysParam["ModelScript"] = "";
}

QStringList global::singleListRegularStr(QString str){
    QRegExp re("[\\[,\\]]");
    QStringList strList = str.split(re, QString::SkipEmptyParts);
    return strList;
}

void global::registerParamter(){
    sysParam["ProjectPath"] = "";
    sysParam["WorkingPath"] = "";
    sysParam["ModelVariables"] = "";
    sysParam["ModelFile"] = "";
    sysParam["ModelScript"] = "";
}

/*void global::setSysParam(const QString &key, const QString &value){
    sysParam[key] = value;
}

QString global::getSysParam(const QString &key){
    return sysParam[key];
}*/
