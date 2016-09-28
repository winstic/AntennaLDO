#include "wizardDesignPerformance.h"

wizardDesignPerformance::wizardDesignPerformance(QJsonObject obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    this->freStartLabel = new QLabel("频段start:");
    this->freEndLabel = new QLabel("频段end:");
    this->freNumberLabel = new QLabel("频点个数:");
    this->sweepTypeLabel = new QLabel("扫频方式:");
    this->PMLabel = new QLabel("极化方式:");
    this->unitLabel = new QLabel("MHz");
    this->freStartEdit = new QLineEdit;
    this->freEndEdit = new QLineEdit;
    this->freNumberEdit = new QLineEdit;
    this->sweeptypeComb = new QComboBox;
    this->PMComb = new QComboBox;
    initComBoBox();
}

void wizardDesignPerformance::wizardDialog(){
    setTitle("频率设置");
    QJsonObject freObj;
    QStringList strList;
    if(this->obj.contains("FreSetting")){
        QJsonValue freValue = obj.value("FreSetting");
        if(freValue.isObject())
            freObj = freValue.toObject();
        strList = singleListRegularStr(freObj.value("FreStart").toString().trimmed());
        freStartEdit->setText(strList[0]);
        strList = singleListRegularStr(freObj.value("FreEnd").toString().trimmed());
        freEndEdit->setText(strList[0]);
        strList = singleListRegularStr(freObj.value("FreNumber").toString().trimmed());
        freNumberEdit->setText(strList[0]);
        strList = singleListRegularStr(freObj.value("SweepType").toString().trimmed());
        sweeptypeComb->setCurrentIndex(QString(strList[0]).toInt());
        strList = singleListRegularStr(freObj.value("PM").toString().trimmed());
        PMComb->setCurrentIndex(QString(strList[0]).toInt());
    }
}

void wizardDesignPerformance::initComBoBox(){
    sweeptypeComb->addItem("等差");
    sweeptypeComb->addItem("等比");

    PMComb->addItem("总增益");
    PMComb->addItem("左旋");
    PMComb->addItem("右旋");
    PMComb->addItem("水平");
    PMComb->addItem("垂直");
}

void wizardDesignPerformance::initLayout(){
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;

    hbox->addWidget(freStartLabel);
    hbox->addWidget(freStartEdit);
    hbox->addWidget(unitLabel);
    vbox->addLayout(hbox);

    hbox->addWidget(freEndLabel);
    hbox->addWidget(freEndEdit);
    hbox->addWidget(unitLabel);
    vbox->addLayout(hbox);

    hbox->addWidget(freNumberLabel);
    hbox->addWidget(freNumberEdit);
    hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vbox->addLayout(hbox);

    hbox->addWidget(sweepTypeLabel);
    hbox->addWidget(sweeptypeComb);
    hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vbox->addLayout(hbox);

    hbox->addWidget(PMLabel);
    hbox->addWidget(PMComb);
    hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vbox->addLayout(hbox);

    setLayout(vbox);
}
