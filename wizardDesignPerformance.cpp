#include "wizardDesignPerformance.h"
#include "global.h"

wizardDesignPerformance::wizardDesignPerformance(QJsonObject obj, QWidget *parent) : QWizardPage(parent){
    setTitle(tr("性能参数设置"));
    setSubTitle(tr("设置频率信息并指定远场范围"));
    this->obj = obj;
    //frequencySetting
    this->freStartLabel = new QLabel("起始频点:");
    this->freEndLabel = new QLabel("终止频点:");
    this->freNumberLabel = new QLabel("频点个数:");
    this->sweepTypeLabel = new QLabel("扫频方式:");
    this->PMLabel = new QLabel("极化方式:");
    this->freStartEdit = new QLineEdit;
    this->freEndEdit = new QLineEdit;
    this->freNumberEdit = new QLineEdit;
    this->sweeptypeComb = new QComboBox;
    this->PMComb = new QComboBox;
    this->groupBoxFrequency = new QGroupBox(tr("频率设置"));

    //farFieldSetting
    this->thetaStartLabel = new QLabel("起始θ:");
    this->thetaEndLabel = new QLabel("终止θ:");
    this->thetaStepLabel = new QLabel("θ步长:");
    this->phiStartLabel = new QLabel("起始φ:");
    this->phiEndLabel = new QLabel("终止φ:");
    this->phiStepLabel = new QLabel("φ步长:");
    this->thetaStartEdit = new QLineEdit;
    this->thetaEndEdit = new QLineEdit;
    this->thetaStepEdit = new QLineEdit;
    this->phiStartEdit = new QLineEdit;
    this->phiEndEdit = new QLineEdit;
    this->phiStepEdit = new QLineEdit;
    this->groupBoxFarField = new QGroupBox(tr("远场范围设置"));
    initComBoBox();
    frequencySetting();
    farFieldSetting();
    initLayout();
}

void wizardDesignPerformance::frequencySetting(){
    QJsonObject freObj;
    QStringList strList;
    if(this->obj.contains("FreSetting")){
        QJsonValue freValue = obj.value("FreSetting");
        if(freValue.isObject()){
            freObj = freValue.toObject();
            strList = global::singleListRegularStr(freObj.value("FreStart").toString().trimmed());
            freStartEdit->setText(strList[0]);
            strList = global::singleListRegularStr(freObj.value("FreEnd").toString().trimmed());
            freEndEdit->setText(strList[0]);
            strList = global::singleListRegularStr(freObj.value("FreNumber").toString().trimmed());
            freNumberEdit->setText(strList[0]);
            //strList = global::singleListRegularStr(freObj.value("SweepType").toString().trimmed());
            sweeptypeComb->setCurrentIndex(0);
            sweeptypeComb->setEnabled(false);
            //strList = global::singleListRegularStr(freObj.value("PM").toString().trimmed());
            //PMComb->setCurrentIndex(QString(strList[0]).toInt());
            PMComb->setCurrentIndex(0);
            PMComb->setEnabled(false);
        }
        else
            QMessageBox::critical(this, tr("Error"), tr("Cannot parse 'FreSetting' in json file"));
    }
}

void wizardDesignPerformance::farFieldSetting(){
    QJsonObject freObj;
    QStringList strList;
    if(this->obj.contains("ThetaPhiStep")){
        QJsonValue freValue = obj.value("ThetaPhiStep");
        if(freValue.isObject()){
            freObj = freValue.toObject();
            strList = global::singleListRegularStr(freObj.value("ThetaLower").toString().trimmed());
            thetaStartEdit->setText(strList[0]);
            strList = global::singleListRegularStr(freObj.value("ThetaUpper").toString().trimmed());
            thetaEndEdit->setText(strList[0]);
            strList = global::singleListRegularStr(freObj.value("ThetaStep").toString().trimmed());
            thetaStepEdit->setText(strList[0]);
            strList = global::singleListRegularStr(freObj.value("PhiLower").toString().trimmed());
            phiStartEdit->setText(strList[0]);
            strList = global::singleListRegularStr(freObj.value("PhiUpper").toString().trimmed());
            phiEndEdit->setText(strList[0]);
            strList = global::singleListRegularStr(freObj.value("PhiStep").toString().trimmed());
            phiStepEdit->setText(strList[0]);
        }
        else
            QMessageBox::critical(this, tr("Error"), tr("Cannot parse 'ThetaPhiStep' in json file"));
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
    //!groupBoxFrequency layout
    QGridLayout *freLayout = new QGridLayout;

    freStartLabel->setAlignment(Qt::AlignRight);
    freLayout->addWidget(freStartLabel, 0, 0);
    freLayout->addWidget(freStartEdit, 0, 1);
    freLayout->addWidget(new QLabel("MHz"), 0, 2);

    freEndLabel->setAlignment(Qt::AlignRight);
    freLayout->addWidget(freEndLabel, 1, 0);
    freLayout->addWidget(freEndEdit, 1, 1);
    freLayout->addWidget(new QLabel("MHz"), 1, 2);

    freNumberLabel->setAlignment(Qt::AlignRight);
    freLayout->addWidget(freNumberLabel, 2, 0);
    freLayout->addWidget(freNumberEdit, 2, 1);

    sweepTypeLabel->setAlignment(Qt::AlignRight);
    freLayout->addWidget(sweepTypeLabel, 3, 0);
    freLayout->addWidget(sweeptypeComb, 3, 1);

    PMLabel->setAlignment(Qt::AlignRight);
    freLayout->addWidget(PMLabel, 4, 0);
    freLayout->addWidget(PMComb, 4, 1);

    groupBoxFrequency->setLayout(freLayout);
    //!

    //!groupBoxFarField layout
    QGridLayout *farFieldLayout = new QGridLayout;
    farFieldLayout->addWidget(thetaStartLabel, 0, 0);
    farFieldLayout->addWidget(thetaStartEdit, 0, 1);
    farFieldLayout->addWidget(thetaEndLabel, 0, 2);
    farFieldLayout->addWidget(thetaEndEdit, 0, 3);
    farFieldLayout->addWidget(thetaStepLabel, 0, 4);
    farFieldLayout->addWidget(thetaStepEdit, 0, 5);
    farFieldLayout->addWidget(phiStartLabel, 1, 0);
    farFieldLayout->addWidget(phiStartEdit, 1, 1);
    farFieldLayout->addWidget(phiEndLabel, 1, 2);
    farFieldLayout->addWidget(phiEndEdit, 1, 3);
    farFieldLayout->addWidget(phiStepLabel, 1, 4);
    farFieldLayout->addWidget(phiStepEdit, 1, 5);
    groupBoxFarField->setLayout(farFieldLayout);
    //!

    //!global layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacerItem(new QSpacerItem(4, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addWidget(groupBoxFrequency);
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addWidget(groupBoxFarField);
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(layout);
    //!
}
