#include "run.h"

Run::Run(){
    this->vbsPath = QString("%1/%2_design.vbs").arg(sysParam["WorkingProjectPath"]).arg(global::getInfoFromRel("Problem"));
    updateVbs();
}

bool Run::updateVbs(){
    //read all infomation from vbsFile
    QFile inFile(vbsPath);
    if(!inFile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(0, QString("Error"), QString("Cannot read file %1").arg(vbsPath));
        return false;
    }
    QTextStream in(&inFile);
    QString str = in.readAll();
    inFile.close();

    //update vbs file(assign paramters)
    QFile outFile(vbsPath);
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QMessageBox::critical(0, QString("Error"), QString("Cannot write file %1").arg(vbsPath));
        return false;
    }
    QString temp;
    for(QMap<QString, QString>::iterator iter = vbsVariables.begin(); iter != vbsVariables.end(); ++iter){
        temp = QString("#%1#").arg(iter.key());
        str.replace(temp, iter.value());
    }
    QTextStream out(&outFile);
    out << str;
    outFile.close();
    return true;
}

void Run::go(){
    QProcess p(0);;
    //p.execute("hfss", QStringList() << "-RunScriptAndExit" << vbsPath);
    p.execute("hfss", QStringList() << "-RunScript" << vbsPath);
    /*if(! p.waitForStarted()){
        QMessageBox::critical(0, QString("Error"), QString("this process can not be called."));
        p.write("quit");
        p.kill();
        return;
    }*/
    p.waitForFinished();
    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
}
