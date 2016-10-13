#include "designtab.h"

designTab::designTab(QJsonObject obj, QWidget *parent) : QDialog(parent){
    this->obj = obj;
    this->tabWidget = new QTabWidget;
    this->firstTab = new QWidget;
    this->secondTab = new QWidget;

    //!first tabwidget
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
    this->groupBoxFrequency = new QGroupBox(QString("频率设置"));

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
    this->groupBoxFarField = new QGroupBox(QString("远场范围设置"));
    initSetupCom();
    frequencySetting();
    farFieldSetting();
    setFirstTabLayout();
    //!

    //!second tab widget
    readDefaultVars();
    variablesSetting();
    //!
    tabWidget->addTab(firstTab, QIcon(""), tr("性能参数设置"));
    //firstTab->setWindowTitle(tr("设置频率信息并指定远场范围"));
    tabWidget->addTab(secondTab, QIcon(""), tr("模型设置"));
    //secondTab->setWindowTitle(tr("模型设置"));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tabWidget);

    this->setWindowTitle(tr("天线设计"));
    this->setMinimumSize(880, 580);
    this->setLayout(layout);
}

//!first tab widget
void designTab::initSetupCom(){
    sweeptypeComb->addItem("等差");
    sweeptypeComb->addItem("等比");

    PMComb->addItem("总增益");
    PMComb->addItem("左旋");
    PMComb->addItem("右旋");
    PMComb->addItem("水平");
    PMComb->addItem("垂直");
}

bool designTab::frequencySetting(){
    QJsonObject freObj = parseJson::getSubJsonObj(obj, "FreSetting");
    if(freObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("designTab.cpp:68: error: Cannot parse 'FreSetting' in json file"));
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

bool designTab::farFieldSetting(){
    QJsonObject farFieldObj = parseJson::getSubJsonObj(obj, "ThetaPhiStep");
    if(farFieldObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("designTab.cpp:91: error: Cannot parse 'ThetaPhiStep' in json file"));
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

void designTab::setFirstTabLayout(){
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
    firstTab->setLayout(layout);
    //!
}
//!

//!sceond widget
bool designTab::readDefaultVars(){
    QJsonObject defaultVarsObj = parseJson::getSubJsonObj(obj, "varsValue");
    if(defaultVarsObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("designTab.cpp:172: error: Cannot parse 'varsValue' in json file"));
        return false;
    }
    for(QJsonObject::iterator iter = defaultVarsObj.begin(); iter != defaultVarsObj.end(); ++ iter){
        defaultVars[iter.key()] = iter.value().toString().trimmed();
    }
    return true;
}

QComboBox* designTab::initUnitComBo(){
    QComboBox *comb = new QComboBox;
    comb->addItem("mm");
    comb->addItem("cm");
    comb->addItem("λ");
    comb->addItem("m");
    comb->addItem("km");
    comb->setCurrentIndex(3);
    return comb;
}

bool designTab::variablesSetting(){
    QJsonObject variablesObj = parseJson::getSubJsonObj(obj, "variables");
    if(variablesObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("designTab.cpp:195: error: Cannot parse 'variables' in json file"));
        return false;
    }
    QJsonObject varObj;
    QString varKey;
    QStringList varValue;
    int posx = 0, valueListLength;
    double realValue;
    QGridLayout *gridLayout = new QGridLayout;
    QRegExp rx("^(-?\\d+)(\\.\\d+)?$");
    QRegExpValidator *floatValid = new QRegExpValidator(rx);      //float

    for(QJsonObject::iterator iter = variablesObj.begin(); iter != variablesObj.end(); ++ iter){
        // iter format: "W1":{"note" : "介质板宽度W1(m)", "W1" : "0.025"}
        varInfo tempVarInfo;
        varKey = iter.key();
        varObj = iter.value().toObject();
        //get note infomation
        QLabel *keyLabel = new QLabel(varObj.value("note").toString().trimmed());
        //keyLabel->setFixedWidth(100);
        keyLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
        gridLayout->addWidget(keyLabel, posx, 0);

        // init line edit and layout
        varValue = global::str2list(varObj.value(varKey).toString().trimmed());
        valueListLength = varValue.length();
        QLineEdit *valueEdit = new QLineEdit;
        valueEdit->setFixedWidth(240);
        valueEdit->setValidator(floatValid);

        if(valueListLength == 1){
            valueEdit->setText(varValue[0]);
            valueEdit->setReadOnly(true);
            gridLayout->addWidget(valueEdit, posx, 1);
        }
        else{
            QVBoxLayout *vLayout = new QVBoxLayout;
            QSlider *varSlider = new QSlider(Qt::Horizontal);

            varSlider->setStyleSheet(getSliderSheet());
            varSlider->setMinimum(0);
            varSlider->setMaximum(100);
            varSlider->setSingleStep(1);

            double stopValue = QString(varValue[1]).trimmed().toDouble();
            double startValue = QString(varValue[0]).trimmed().toDouble();
            realValue = defaultVars[varKey].trimmed().toDouble();
            int sliderValue = 100 * (realValue - startValue) / (stopValue - startValue);
            //realValue =startValue + (varSlider->value()*1.0 / 100) *(stopValue - startValue);
            //!conversion slider value and edit value
            //!

            varSlider->setValue(sliderValue);
            valueEdit->setText(QString::number(realValue));

            //valueEdit->setReadOnly(true);
            vLayout->addWidget(valueEdit);
            vLayout->addWidget(varSlider);
            //design inner space
            vLayout->setSpacing(0);
            // design outer space
            //vLayout->setMargin(0);
            gridLayout->addLayout(vLayout, posx, 1);

            tempVarInfo.lower = startValue;
            tempVarInfo.upper = stopValue;
            tempVarInfo.varSlider = varSlider;

            //connect(varSlider, SIGNAL(valueChanged(int)), this, SLOT(slot_sliderValueChange(int)));

        }
        tempVarInfo.varKey = varKey;
        tempVarInfo.varEdit = valueEdit;
        varinfos.append(tempVarInfo);
        //connect(valueEdit, SIGNAL(textChanged(QString)), this, SLOT(slot_LinetextChange(QString)));
        //valueEdit->installEventFilter(this);        //install filter in this dialog(在对话框上为QLineEdit安装过滤器)
        //connect(valueEdit, SIGNAL(), this, SLOT(slot_LinetextChange(QString)));
        QComboBox *unitComBo = initUnitComBo();
        unitComBo->setFixedWidth(50);
        gridLayout->addWidget(unitComBo, posx, 2);
        ++ posx;
    }

    gridLayout->setAlignment(Qt::AlignHCenter);
    gridLayout->setAlignment(Qt::AlignVCenter);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setSpacing(10);

    //!add picture
    QString picturePath;
    QSqlQuery sqlQuery;
    QString sql = QString("select pModelPath from antennaProblem where pName = '%1';")
            .arg(global::getInfoFromRel("Problem"));
    sqlQuery.prepare(sql);
    if(!sqlQuery.exec(sql)){
        qDebug() << sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            picturePath = sqlQuery.value("pModelPath").toString();
        }
    }
    QLabel *atnPhoto = new QLabel;
    QPixmap pm = QPixmap(picturePath);
    atnPhoto->setPixmap(pm.scaled(440, 400));
    //!
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addLayout(gridLayout);
    hLayout->addWidget(atnPhoto);

    QVBoxLayout *tabLayout = new QVBoxLayout;
    tabLayout->addSpacerItem(new QSpacerItem(3, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    tabLayout->addLayout(hLayout);
    tabLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    secondTab->setLayout(tabLayout);
    return true;
}

QString designTab::getSliderSheet(){
    return QString("  \
         QSlider\
         {     \
            spacing: 0px;\
            min-height:8px;\
            max-height:8px;\
            min-width:240px;\
            max-width:240px;\
         }\
         QSlider::add-page:Horizontal\
         {     \
            background-color: rgb(222, 231, 234);\
            height:8px;\
         }\
         QSlider::sub-page:Horizontal \
        {\
            background-color: rgb(37, 168, 198);\
            height:8px;\
         }\
        QSlider::groove:Horizontal \
        {\
            background:transparent;\
            height:8px;\
        }\
        QSlider::handle:Horizontal \
        {\
             height: 13px;\
            width:13px;\
            border-image: url(./images/dot_16px.png);\
             margin: 0px; \
         }\
        ");
}
//!
