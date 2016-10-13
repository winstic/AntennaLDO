#include "run.h"

Run::Run(){
    this->designDir = sysParam["CurrentDesignPath"];
    this->atnName = global::getInfoFromRel("Problem");
    this->vbsPath = QString("%1/%2_design.vbs").arg(designDir).arg(atnName);
    //vbsVars
    this->obj = parseJson::getJsonObj(QString("%1/%2_conf.json").arg(designDir).arg(atnName));
}

bool Run::registerHfssVars(){
    //copy hfss file in designDir from projectDir
    global::copyFile(QString("%1/%2.hfss").arg(sysParam["WorkingProjectPath"]).arg(atnName), designDir);
    vbsVars["hfsspath"] = QString("%1/%2").arg(designDir).arg(atnName);
    vbsVars["hfssname"] = atnName;
    QJsonObject varsValueObj = parseJson::getSubJsonObj(obj, "varsValue");
    QJsonObject freObj = parseJson::getSubJsonObj(obj, "FreSetting");
    QJsonObject farfieldObj = parseJson::getSubJsonObj(obj, "ThetaPhiStep");
    if(varsValueObj.isEmpty() || freObj.isEmpty() || farfieldObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("run.cpp:18: error: Cannot register Hfss Vars"));
        return false;
    }
    for(QJsonObject::iterator iter = varsValueObj.begin(); iter != varsValueObj.end(); ++ iter){
        vbsVars[iter.key()] = iter.value().toString().trimmed();
    }
    QStringList strList;
    strList = global::str2list(freObj.value("FreStart").toString().trimmed());
    vbsVars["FreStart"] = M2GHz(strList[0]);
    strList = global::str2list(freObj.value("FreEnd").toString().trimmed());
    vbsVars["FreEnd"] = M2GHz(strList[0]);
    strList = global::str2list(freObj.value("FreNumber").toString().trimmed());
    vbsVars["FreNumber"] = strList[0];
    strList = global::str2list(freObj.value("SweepType").toString().trimmed());
    vbsVars["SweepType"] = strList[0];
    strList = global::str2list(freObj.value("PM").toString().trimmed());
    vbsVars["PM"] = strList[0];

    vbsVars["Freq"] = QString::number((vbsVars["FreStart"].toDouble() + vbsVars["FreEnd"].toDouble()) / 2000.0);
    for(QJsonObject::iterator iter = farfieldObj.begin(); iter != farfieldObj.end(); ++ iter){
        strList = global::str2list(iter.value().toString().trimmed());
        vbsVars[iter.key()] = strList[0];
    }
    return true;
}

bool Run::updateVbs(){
    //read all infomation from vbsFile
    QFile inFile(vbsPath);
    if(!inFile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(0, QString("Error"), QString("run.cpp:48: error: Cannot read file %1").arg(vbsPath));
        return false;
    }
    QTextStream in(&inFile);
    QString str = in.readAll();
    inFile.close();

    //update vbs file(assign paramters)
    QFile outFile(vbsPath);
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QMessageBox::critical(0, QString("Error"), QString("run.cpp:58: error: Cannot write file %1").arg(vbsPath));
        return false;
    }
    QString temp;
    for(QMap<QString, QString>::iterator iter = vbsVars.begin(); iter != vbsVars.end(); ++iter){
        temp = QString("#%1#").arg(iter.key());
        str.replace(temp, iter.value());
    }
    QTextStream out(&outFile);
    out << str;
    outFile.close();
    return true;
}

QString Run::M2GHz(QString mhz){
    double doubleGHz = mhz.toDouble() / 1000.0;
    return QString::number(doubleGHz);
}

bool Run::go(){
    bool isReady = false;
    if(registerHfssVars())
        isReady = updateVbs();
    if(isReady){
        QProcess p(0);;
        //p.execute("hfss", QStringList() << "-RunScriptAndExit" << vbsPath);
        int a = p.execute("hfss", QStringList() << "-RunScript" << vbsPath);
        /*if(! p.waitForStarted()){
            QMessageBox::critical(0, QString("Error"), QString("this process can not be called."));
            p.write("quit");
            p.kill();
            return;
        }*/
        qDebug() << a;
        p.waitForFinished();
        qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
    }
    return isReady;
}
