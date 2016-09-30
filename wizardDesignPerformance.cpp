#include "wizardDesignPerformance.h"

wizardDesignPerformance::wizardDesignPerformance(QJsonObject obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    this->freStartLabel = new QLabel("频段start:");
    this->freEndLabel = new QLabel("频段end:");
    this->freNumberLabel = new QLabel("频点个数:");
    this->sweepTypeLabel = new QLabel("扫频方式:");
    this->PMLabel = new QLabel("极化方式:");
    this->freStartEdit = new QLineEdit;
    this->freEndEdit = new QLineEdit;
    this->freNumberEdit = new QLineEdit;
    this->sweeptypeComb = new QComboBox;
    this->PMComb = new QComboBox;
    initComBoBox();
    wizardDialog();
    initLayout();
}

void wizardDesignPerformance::wizardDialog(){
    setTitle("频率设置");
    QJsonObject freObj;
    QStringList strList;
    if(this->obj.contains("FreSetting")){
        QJsonValue freValue = obj.value("FreSetting");
        if(freValue.isObject()){
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
        else
            QMessageBox::critical(this, tr("Error"), tr("Cannot parse 'FreSetting' in json file"));
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
    QGridLayout *gridLayout = new QGridLayout;

    freStartLabel->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(freStartLabel, 0, 0);
    freStartEdit->setFixedWidth(240);
    gridLayout->addWidget(freStartEdit, 0, 1);
    gridLayout->addWidget(new QLabel("MHz"), 0, 2);

    freEndLabel->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(freEndLabel, 1, 0);
    freEndEdit->setFixedWidth(240);
    gridLayout->addWidget(freEndEdit, 1, 1);
    gridLayout->addWidget(new QLabel("MHz"), 1, 2);

    freNumberLabel->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(freNumberLabel, 2, 0);
    freNumberEdit->setFixedWidth(240);
    gridLayout->addWidget(freNumberEdit, 2, 1);

    sweepTypeLabel->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(sweepTypeLabel, 3, 0);
    sweeptypeComb->setFixedWidth(240);
    gridLayout->addWidget(sweeptypeComb, 3, 1);

    PMLabel->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(PMLabel, 4, 0);
    PMComb->setFixedWidth(240);
    gridLayout->addWidget(PMComb, 4, 1);

    setLayout(gridLayout);
}
