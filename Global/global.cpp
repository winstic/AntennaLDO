#include "global.h"
#include <QMessageBox>
#include <QTextStream>

QMap<QString, QString> sysParam;
global::global(){}

QStringList global::str2list(QString str){
    QRegExp re("[\\[,'\\]]");
    QStringList strList = str.split(re, QString::SkipEmptyParts);
    return strList;
}

QString global::str2liststr(const QString &str){
    return QString("[%1]").arg(str);
}

void global::registerParamter(){
    sysParam["DefaultProjectPath"] = "";
    sysParam["WorkingProjectPath"] = "";
    sysParam["CurrentDesignPath"] = "";
    sysParam["CurrentOptimizePath"] = "";
    //sysParam["Algorithm"] = "";
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
        QMessageBox::critical(0, QString("Error"), QString("global.cpp:42: error: rel文件缺失"));
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

/*bool global::addedInfoInRel(const QString &key, const QString &value){
    QFile outfile(QString("%1/%2.rel").arg(sysParam["WorkingProjectPath"]).arg(getProjectName()));
    if (!outfile.open(QFile::WriteOnly | QIODevice::Append)){
        QMessageBox::critical(0, QString("Error"), QString("global.cpp:64: error: rel文件缺失"));
        return false;
    }
    QTextStream out(&outfile);
    out << key << ":" << value;
    outfile.close();
    return true;
}
*/
QString global::getProjectName(){
    QString dirPath = sysParam["WorkingProjectPath"];
    if(dirPath.isNull() || dirPath.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("global.cpp:62: error: 找不到工作目录"));
        return NULL;
    }
    QStringList nameList = dirPath.split("/");
    return nameList.at(nameList.length()-1);
}

bool global::copyFile(QString sourceFile, QString targetFile, bool coverFileIfExist){
    QString sourceDir = QDir(sourceFile).absolutePath();
    QString targetDir = QDir(targetFile).absolutePath();
    if(sourceDir == targetDir){
        return true;
    }
    if(! QFile::exists(sourceDir)){
        return false;
    }
    QDir* createFile = new QDir;
    bool isExist = createFile->exists(targetDir);
    if(isExist && coverFileIfExist){
        createFile->remove(targetDir);
    }
    //copy function: if targetDir already exist then return false
    if(! QFile::copy(sourceDir, targetDir)){
        return false;
    }
    return true;
}
