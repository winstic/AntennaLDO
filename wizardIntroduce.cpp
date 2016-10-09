#include "wizardIntroduce.h"

wizardIntroduce::wizardIntroduce(QString antennaName, QWidget *parent) : QWizardPage(parent){
    atnName = antennaName;
    setTitle(atnName);
    atnInfo = new QTextEdit;
    atnInfo->setReadOnly(true);
    atnPhoto = new QLabel;

    setAtnIntroduceInfo(antennaName);
    atnInfo->setText(info);
    QPixmap mPixmap = QPixmap(photo);
    atnPhoto->setPixmap(mPixmap.scaled(440, 400));

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
            info = sqlQuery.value("pInfo").toString();
            photo = sqlQuery.value("pModelPath").toString();
        }
    }
}

wizardIntroduce::~wizardIntroduce(){}
