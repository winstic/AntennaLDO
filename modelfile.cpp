#include "modelfile.h"

modelFile::modelFile(QString antennaName, QWidget *parent) : QDialog(parent){
    //remove help menu
    this->setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    this->setMinimumSize(880, 580);

    //atnName = global::getInfoFromRel("Problem");
    atnName = antennaName;
    atnInfo = new QTextEdit;
    atnInfo->setReadOnly(true);

    info = getAtnModelInfo(atnName);
    atnInfo->setText(info);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(atnInfo);
    setLayout(layout);
}

QString modelFile::getAtnModelInfo(const QString name){
    QSqlQuery sqlQuery;
    QString sql = QString("select pModelPath, pInfo from antennaProblem where pName = '%1';").arg(name);
    sqlQuery.prepare(sql);
    if(!sqlQuery.exec(sql)){
        qDebug() << sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            return sqlQuery.value("pInfo").toString();
        }
    }
}
