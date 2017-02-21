#include "../Global/global.h"
#include "wizardDesignPerformance.h"

wizardDesignPerformance::wizardDesignPerformance(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    setTitle(tr("性能参数设置"));
    setSubTitle(tr("设置频率信息并指定远场范围"));
    this->obj = obj;
    //frequencySetting
    this->freStartLabel = new QLabel("频段上限:");
    this->freEndLabel = new QLabel("频段下限:");
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

    //set regexp
    //QRegExpValidator *posFloatValid = new QRegExpValidator(QRegExp("^(-?\\d+)(\\.\\d+)?$"));    //positive float
    QRegExpValidator *nonNegFloatValid = new QRegExpValidator(QRegExp("^(\\d+)(\\.\\d+)?$"));    //non negative float
    QRegExpValidator *floatValid = new QRegExpValidator(QRegExp("^-?(180|1?[0-7]?\\d(\\.\\d+)?)$"));      //float [-180. 180]
    QRegExpValidator *posIntValid = new QRegExpValidator(QRegExp("^[0-9]*[1-9][0-9]*$"));   //positive int
    freStartEdit->setValidator(nonNegFloatValid);
    freEndEdit->setValidator(nonNegFloatValid);
    freNumberEdit->setValidator(posIntValid);
    thetaStartEdit->setValidator(floatValid);
    thetaEndEdit->setValidator(floatValid);
    thetaStepEdit->setValidator(nonNegFloatValid);
    phiStartEdit->setValidator(floatValid);
    phiEndEdit->setValidator(floatValid);
    phiStepEdit->setValidator(nonNegFloatValid);

    initComBoBox();
    frequencySetting();
    farFieldSetting();
    initLayout();
    //connect(thetaStartEdit, )
}

bool wizardDesignPerformance::frequencySetting(){
    QJsonObject freObj = parseJson::getSubJsonObj(obj, "FreSetting");
    if(freObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardDesignPerformance.cpp:61: error: Cannot parse 'FreSetting' in json file"));
        return false;
    }
    QStringList strList;
    strList = global::str2list(freObj.value("FreStart").toString().trimmed());
    freStartEdit->setText(strList[0]);
    strList = global::str2list(freObj.value("FreEnd").toString().trimmed());
    freEndEdit->setText(strList[0]);
    strList = global::str2list(freObj.value("FreNumber").toString().trimmed());
    freNumberEdit->setText(strList[0]);
    //strList = global::str2list(freObj.value("SweepType").toString().trimmed());
    sweeptypeComb->setCurrentIndex(0);
    sweeptypeComb->setEnabled(false);
    //strList = global::str2list(freObj.value("PM").toString().trimmed());
    //PMComb->setCurrentIndex(QString(strList[0]).toInt());
    PMComb->setCurrentIndex(0);
    PMComb->setEnabled(false);
    return true;
}

bool wizardDesignPerformance::farFieldSetting(){
    QJsonObject farFieldObj = parseJson::getSubJsonObj(obj, "ThetaPhiStep");
    if(farFieldObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardDesignPerformance.cpp:84: error: Cannot parse 'ThetaPhiStep' in json file"));
        return false;
    }
    QStringList strList;
    strList = global::str2list(farFieldObj.value("ThetaLower").toString().trimmed());
    thetaStartEdit->setText(strList[0]);
    strList = global::str2list(farFieldObj.value("ThetaUpper").toString().trimmed());
    thetaEndEdit->setText(strList[0]);
    strList = global::str2list(farFieldObj.value("ThetaStep").toString().trimmed());
    thetaStepEdit->setText(strList[0]);
    strList = global::str2list(farFieldObj.value("PhiLower").toString().trimmed());
    phiStartEdit->setText(strList[0]);
    strList = global::str2list(farFieldObj.value("PhiUpper").toString().trimmed());
    phiEndEdit->setText(strList[0]);
    strList = global::str2list(farFieldObj.value("PhiStep").toString().trimmed());
    phiStepEdit->setText(strList[0]);
    return true;
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
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(groupBoxFrequency);
    vlayout->addWidget(groupBoxFarField);
    vlayout->setSpacing(50);
    vlayout->setContentsMargins(2,20,2,2);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(vlayout);
    setLayout(layout);
    //!
}

QJsonObject wizardDesignPerformance::saveInJsonObj(){
    QJsonObject saveObj, saveFreObj, saveFarObj;
    qDebug() << "start";
    //qDebug() << "ff" << freStartEdit;
    //saveFreObj.insert("FreStart", QString("[%1]").arg(freStartEdit->text().trimmed()));
    saveFreObj.insert("FreStart", "[2400]");
    saveFreObj.insert("FreEnd", QString("[%1]").arg(freEndEdit->text().trimmed()));
    saveFreObj.insert("FreNumber", QString("[%1]").arg(freNumberEdit->text().trimmed()));
    saveFreObj.insert("SweepType", QString("[%1]").arg(sweeptypeComb->currentIndex()));
    saveFreObj.insert("PM", QString("[%1]").arg(PMComb->currentIndex()));

    saveFarObj.insert("ThetaLower", QString("[%1]").arg(thetaStartEdit->text().trimmed()));
    saveFarObj.insert("ThetaUpper", QString("[%1]").arg(thetaEndEdit->text().trimmed()));
    saveFarObj.insert("ThetaStep", QString("[%1]").arg(thetaStepEdit->text().trimmed()));
    saveFarObj.insert("PhiLower", QString("[%1]").arg(phiStartEdit->text().trimmed()));
    saveFarObj.insert("PhiUpper", QString("[%1]").arg(phiEndEdit->text().trimmed()));
    saveFarObj.insert("PhiStep", QString("[%1]").arg(phiStepEdit->text().trimmed()));

    saveObj.insert("FreSetting", saveFreObj);
    saveObj.insert("ThetaPhiStep", saveFarObj);
    qDebug() << "end";
    return saveObj;
}

bool wizardDesignPerformance::validatePage(){
    return true;
}
