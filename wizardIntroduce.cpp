#include "wizardIntroduce.h"

wizardIntroduce::wizardIntroduce(QString antennaName, QWidget *parent) : QWizardPage(parent){
    atnName = antennaName;
    setTitle(atnName);
    atnInfo = new QTextEdit;
    atnInfo->setReadOnly(true);
    atnPhoto = new QLabel;
    setAtnIntroduceInfo(antennaName);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(atnInfo);
    layout->addWidget(atnPhoto);
    setLayout(layout);
}

void wizardIntroduce::setAtnIntroduceInfo(QString name){
    QSqlQuery sqlQuery;
    QString sql = QString("select pModelPath, pInfo from antennaProblem where pName = '%1';").arg(name);
    sqlQuery.prepare(sql);
    if(!sqlQuery.exec(sql)){
        qDebug() << sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            atnInfo->setText(sqlQuery.value("pInfo").toString());
            atnPhoto->setPixmap(QPixmap(sqlQuery.value("pModelPath").toString()));
        }
    }
}

wizardIntroduce::~wizardIntroduce(){}
