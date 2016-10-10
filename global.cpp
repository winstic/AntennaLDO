#include "global.h"
#include <QMessageBox>
#include <QTextStream>

QMap<QString, QString> sysParam;
QMap<QString, QString> vbsVariables;
global::global(){}

QStringList global::singleListRegularStr(QString str){
    QRegExp re("[\\[,\\]]");
    QStringList strList = str.split(re, QString::SkipEmptyParts);
    return strList;
}

void global::registerParamter(){
    sysParam["DefaultProjectPath"] = "";
    sysParam["WorkingProjectPath"] = "";
    //sysParam["ProjectName"] = "";
    //sysParam["ProblemName"] = "";
    //sysParam["ModelVariablesPath"] = "";        //.json file
    //sysParam["ModelFilePath"] = "";             //.hfss, .feko ....
    //sysParam["ModelScriptPath"] = "";           //.vbs
    //sysParam["TreeStructPath"] = "";            //.xml
}

QString global::getFileBySuffix(const QString &dir, const QString &suff){
    QFileInfoList fileList = QDir(dir).entryInfoList();
    foreach (QFileInfo fileInfo, fileList) {
        if(!fileInfo.isFile()) continue;
        if(0 == fileInfo.suffix().compare(suff, Qt::CaseInsensitive))
            return fileInfo.filePath();
    }
    return NULL;
}

QString global::getInfoFromRel(const QString &key){
    QFile infile(QString("%1/%2.rel").arg(sysParam["WorkingProjectPath"]).arg(getProjectName()));
    if (!infile.open(QFile::Text|QFile::ReadOnly)){
        QMessageBox::warning(0, "警告！", "rel文件缺失", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return NULL;
    }
    QTextStream txtInput(&infile);
    QString str = txtInput.readAll();
    infile.close();

    QStringList strList = str.split("\n", QString::SkipEmptyParts);
    for(int i = 0 ; i < strList.count(); ++ i){
        if(strList.at(i).contains(key)){
            QStringList tempList = QString(strList.at(i)).split(":");
            return tempList.at(1).trimmed();
        }
    }
    return NULL;
}

QString global::getProjectName(){
    QString dirPath = sysParam["WorkingProjectPath"];
    if(dirPath.isNull() || dirPath.isEmpty()){
        QMessageBox::warning(0, "警告！", "找不到工作目录", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return NULL;
    }
    QStringList nameList = dirPath.split("/");
    return nameList.at(nameList.length()-1);
}
