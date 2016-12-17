#include "optimizeRun.h"

optimizeRun::optimizeRun() : atnName(""), algorithmName(""), atnPath(""),
    algorithmPath(""), DEA4ADPath(""){
    this->optimizeDir = sysParam["CurrentOptimizePath"];
}

void optimizeRun::setInfo(){
    QString globalConfPath, atnSqlStr, algSqlStr;
    QJsonObject globalObj;
    globalConfPath = QString("%1/global_conf.json").arg(optimizeDir);
    globalObj = parseJson::getJsonObj(globalConfPath);
    atnName = globalObj.value("PROBLEM_NAME").toString().trimmed();
    algorithmName = globalObj.value("ALGORITHM_NAME").toString().trimmed();
    atnSqlStr = QString("select proPath from antennaProblem where pName = '%1';").arg(atnName);
    algSqlStr = QString("select algPath from algorithm where aName = '%1';").arg(algorithmName);
    QSqlQuery sqlQuery;
    sqlQuery.prepare(atnSqlStr);
    if(!sqlQuery.exec(atnSqlStr)){
        qDebug()<< sqlQuery.lastError();
    }
    else{
        sqlQuery.next();
        atnPath = sqlQuery.value("proPath").toString();
    }
    sqlQuery.prepare(algSqlStr);
    if(!sqlQuery.exec(algSqlStr)){
        qDebug()<< sqlQuery.lastError();
    }
    else{
        sqlQuery.next();
        algorithmPath = sqlQuery.value("algPath").toString();
    }
    DEA4ADPath = QString("./DEA4AD/trunk");
    qDebug() << atnPath << "\n" << algorithmPath;
}

bool optimizeRun::update2DEA4AD(){
    if(! global::copyFile(QString("%1/global_conf.json").arg(optimizeDir), QString("%1/global_conf.json").arg(DEA4ADPath)) ||
            ! global::copyFile(QString("%1/algorithm_conf.json").arg(optimizeDir), QString("%1/%2_conf.json").arg(algorithmPath).arg(algorithmName)) ||
            ! global::copyFile(QString("%1/%2_conf.json").arg(optimizeDir).arg(atnName), QString("%1/%2_conf.json").arg(atnPath).arg(atnName))){
        QMessageBox::critical(0, QString("Error"), QString("optimizeRun.cpp:40: error: 优化模块DEA4AD文件更新失败！"));
        return false;
    }
    return true;
}

void optimizeRun::run(){
    QProcess p(0);
    setInfo();
    update2DEA4AD();
    p.execute("python.exe", QStringList() << QString("%1/start.py").arg(DEA4ADPath));
    p.waitForFinished();
    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
}
