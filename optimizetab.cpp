#include "optimizetab.h"

optimizeTab::optimizeTab(QJsonObject obj, QWidget *parent) : QDialog(parent){
    this->setWindowTitle(tr("天线优化"));
    this->obj = obj;
    this->tabWidget = new QTabWidget;
    this->setMinimumSize(880, 580);
    //remove help menu
    this->setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    this->firstTab = new QWidget;
    this->secondTab = new QWidget;
    this->thirdTab = new QWidget;
    this->fourthTab = new QWidget;
    this->saveAllButton = new QPushButton("保存所有");
    connect(saveAllButton, SIGNAL(clicked(bool)), this, SLOT(slot_saveAllButton(bool)));

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

    //gain axial loss setting
    this->gainTable = new QTableWidget;
    this->axialTable = new QTableWidget;
    this->lossTable = new QTableWidget;
    this->groupBoxGain = new QGroupBox(QString("增益设置"));
    this->groupBoxAxial = new QGroupBox(tr("轴比设置"));
    this->groupBoxLoss = new QGroupBox(tr("回波损失"));
    this->gainsignalsmap = new QSignalMapper();
    this->axialsignalsmap = new QSignalMapper();
    this->losssignalsmap = new QSignalMapper();

    //variables setting
    this->varTable = new QTableWidget;
    this->signalsmap = new QSignalMapper;

    //algorithm setting
    this->atnName = global::getInfoFromRel("Problem");
    this->algLabel = new QLabel(tr("选择算法:"));
    this->generationLabel = new QLabel(tr("最大代数"));
    this->popsizeLabel = new QLabel(tr("种群规模"));
    this->threadLabel = new QLabel(tr("启动进程数"));
    this->algCombo = new QComboBox();
    this->generationLine = new QLineEdit();
    this->popsizeLine = new QLineEdit();
    this->threadLine = new QLineEdit();

    //!first tab widget
    initSetupCom();
    frequencySetting();
    farFieldSetting();
    setFirstTabLayout();
    //!
    //!second tab widget
    gainSetting();
    axialSetting();
    lossSetting();
    setSecondTabLayout();
    //!

    //!third tab widget
    wizardDialog();
    //!

    //!fourth tab widget
    setAlgComboItem(atnName);
    this->globalObj = parseJson::getJsonObj(QString("%1/global_conf.json").arg(sysParam["CurrentOptimizePath"]));
    this->algObj = parseJson::getJsonObj(QString("%1/algorithm_conf.json").arg(sysParam["CurrentOptimizePath"]));
    this->algName = globalObj.value("ALGORITHM_NAME").toString().trimmed();
    this->algCombo->setCurrentText(algName);
    getConfInfo();
    setFourthTabLayout();
    connect(algCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_algName(int)));
    //!

    tabWidget->addTab(firstTab, QIcon(""), tr("性能参数设置"));
    //firstTab->setWindowTitle(tr("设置频率信息并指定远场范围"));
    tabWidget->addTab(secondTab, QIcon(""), tr("增益轴比设置"));
    //secondTab->setWindowTitle(tr("模型设置"));
    //QScrollArea *scrollArea = new QScrollArea;
    //scrollArea->setWidget(tabWidget);
    tabWidget->addTab(thirdTab, QIcon(""), tr("模型设置"));
    tabWidget->addTab(fourthTab, QIcon(""), tr("算法设置"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    buttonLayout->addWidget(saveAllButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tabWidget);
    layout->addLayout(buttonLayout);

    this->setLayout(layout);
}

//!first tab widget
void optimizeTab::initSetupCom(){
    sweeptypeComb->addItem("等差");
    sweeptypeComb->addItem("等比");

    PMComb->addItem("总增益");
    PMComb->addItem("左旋");
    PMComb->addItem("右旋");
    PMComb->addItem("水平");
    PMComb->addItem("垂直");
}

bool optimizeTab::frequencySetting(){
    QJsonObject freObj = parseJson::getSubJsonObj(obj, "FreSetting");
    if(freObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("optimizeTab.cpp:126: error: Cannot parse 'FreSetting' in json file"));
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

bool optimizeTab::farFieldSetting(){
    QJsonObject farFieldObj = parseJson::getSubJsonObj(obj, "ThetaPhiStep");
    if(farFieldObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("optimizeTab.cpp:149: error: Cannot parse 'ThetaPhiStep' in json file"));
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

void optimizeTab::setFirstTabLayout(){
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
    layout->addWidget(groupBoxFrequency);
    layout->addWidget(groupBoxFarField);
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->setSpacing(100);
    layout->setContentsMargins(2,50,2,50);
    firstTab->setLayout(layout);
    //!
}
//!
//!second tab widget
bool optimizeTab::gainSetting(){
    gainTable->setColumnCount(8);
    QStringList header;
    header << "起始θ" << "终止θ" << "起始φ" << "终止φ" << "优化方式" << "误差值" << "增益(dB)" << "权值";
    gainTable->setHorizontalHeaderLabels(header);
    //gainTable->setStyleSheet("QTableView {selection-background-color: grey;}");
    gainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //qDebug() << gainTable->width();
    QJsonObject gainObj = parseJson::getSubJsonObj(obj, "GainSetting");
    if(gainObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("optimizeTab.cpp:237: error: Cannot parse 'GainSetting' in json file"));
        return false;
    }
    QStringList strListThetaLower = global::str2list(gainObj.value("Theta_Lower_gain").toString());
    QStringList strListThetaUpper = global::str2list(gainObj.value("Theta_Upper_gain").toString());
    QStringList strListPhiLower = global::str2list(gainObj.value("Phi_Lower_gain").toString());
    QStringList strListPhiUpper = global::str2list(gainObj.value("Phi_Upper_gain").toString());
    QStringList strListOptimaltype = global::str2list(gainObj.value("optimaltype_gain").toString());
    QStringList strListDelta = global::str2list(gainObj.value("delta_gain").toString());
    QStringList strListGainobj = global::str2list(gainObj.value("gainobj").toString());
    QStringList strListWeight = global::str2list(gainObj.value("weight_gain").toString());
    gainTable->setRowCount(strListThetaLower.length());
    for(int i = 0; i < strListThetaLower.length(); i++){
        insert2table(gainTable, i, cthetalower, strListThetaLower[i]);
        insert2table(gainTable, i, cthetaupper, strListThetaUpper[i]);
        insert2table(gainTable, i, cphilower, strListPhiLower[i]);
        insert2table(gainTable, i, cphiupper, strListPhiUpper[i]);

        QComboBox *optimalType = new QComboBox;
        initOptimalTypeComBox(optimalType);
        optimalType->setCurrentText(strListOptimaltype[i]);
        gainTable->setCellWidget(i, coptimaltype, optimalType);
        //qDebug() << gainTable->item(i, coptimaltype)->text();
        //map combobox signal
        connect(optimalType, SIGNAL(currentIndexChanged(int)), gainsignalsmap, SLOT(map()));
        gainsignalsmap->setMapping(optimalType, QString("%1-%2").arg(i).arg(coptimaltype));

        insert2table(gainTable, i, cdelta, strListDelta[i]);
        //setting cannot edit when optimize type is not delta
        if(optimalType->currentIndex() != 2)
            gainTable->item(i, cdelta)->setFlags(Qt::NoItemFlags);

        insert2table(gainTable, i, cobjvalue, strListGainobj[i]);
        insert2table(gainTable, i, cweight, strListWeight[i]);
    }
    connect(gainsignalsmap, SIGNAL(mapped(QString)), this, SLOT(slot_gainChangeOptimaltype(QString)));
    return true;
}

bool optimizeTab::axialSetting(){
    axialTable->setColumnCount(8);
    QStringList header;
    header << "起始θ" << "终止θ" << "起始φ" << "终止φ" << "优化方式" << "误差值" << "轴比(dB)" << "权值";
    axialTable->setHorizontalHeaderLabels(header);
    axialTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonObject axialObj = parseJson::getSubJsonObj(obj, "AxialratioSetting");
    if(axialObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("optimizeTab.cpp:285: error: Cannot parse 'AxialratioSetting' in json file"));
        return false;
    }
    QStringList strListThetaLower = global::str2list(axialObj.value("Theta_Lower_axial").toString());
    QStringList strListThetaUpper = global::str2list(axialObj.value("Theta_Upper_axial").toString());
    QStringList strListPhiLower = global::str2list(axialObj.value("Phi_Lower_axial").toString());
    QStringList strListPhiUpper = global::str2list(axialObj.value("Phi_Upper_axial").toString());
    QStringList strListOptimaltype = global::str2list(axialObj.value("optimaltype_axial").toString());
    QStringList strListDelta = global::str2list(axialObj.value("delta_axial").toString());
    QStringList strListGainobj = global::str2list(axialObj.value("axialobj").toString());
    QStringList strListWeight = global::str2list(axialObj.value("weight_axial").toString());
    axialTable->setRowCount(strListThetaLower.length());
    for(int i = 0; i < strListThetaLower.length(); i++){
        insert2table(axialTable, i, cthetalower, strListThetaLower[i]);
        insert2table(axialTable, i, cthetaupper, strListThetaUpper[i]);
        insert2table(axialTable, i, cphilower, strListPhiLower[i]);
        insert2table(axialTable, i, cphiupper, strListPhiUpper[i]);

        QComboBox *optimalType = new QComboBox;
        initOptimalTypeComBox(optimalType);
        optimalType->setCurrentText(strListOptimaltype[i]);
        axialTable->setCellWidget(i, coptimaltype, optimalType);
        //map combobox signal
        connect(optimalType, SIGNAL(currentIndexChanged(int)), axialsignalsmap, SLOT(map()));
        axialsignalsmap->setMapping(optimalType, QString("%1-%2").arg(i).arg(coptimaltype));

        insert2table(axialTable, i, cdelta, strListDelta[i]);
        //setting cannot edit when optimize type is delta
        if(optimalType->currentIndex() != 2)
            axialTable->item(i, cdelta)->setFlags(Qt::NoItemFlags);

        insert2table(axialTable, i, cobjvalue, strListGainobj[i]);
        insert2table(axialTable, i, cweight, strListWeight[i]);
    }
    connect(axialsignalsmap, SIGNAL(mapped(QString)), this, SLOT(slot_axialChangeOptimaltype(QString)));
    return true;
}

bool optimizeTab::lossSetting(){
    lossTable->setColumnCount(9);
    QStringList header;
    header << "Z0实部" << "Z0虚部" << "损失方式" << "优化方式" << "误差实部" << "误差虚部" << "值实部" << "值虚部" << "权值";
    lossTable->setHorizontalHeaderLabels(header);
    lossTable->resizeColumnToContents(6);
    lossTable->resizeColumnToContents(7);
    lossTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonObject lossObj = parseJson::getSubJsonObj(obj, "VSWRSetting");
    if(lossObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("optimizeTab.cpp:334: error: Cannot parse 'VSWRSetting' in json file"));
        return false;
    }
    QStringList strListR0Real = global::str2list(lossObj.value("R0_real").toString());
    QStringList strListR0imag = global::str2list(lossObj.value("R0_imag").toString());
    QStringList strListReturnLossType = global::str2list(lossObj.value("ReturnLossType").toString());
    QStringList strListOptimaltype = global::str2list(lossObj.value("optimaltype_vswr").toString());
    QStringList strListDeltaReal = global::str2list(lossObj.value("delta_real").toString());
    QStringList strListDeltaImag = global::str2list(lossObj.value("delta_imag").toString());
    QStringList strListVswrobj = global::str2list(lossObj.value("vswrobj").toString());
    QStringList strListS11 = global::str2list(lossObj.value("S11").toString());
    QStringList strListR1Real = global::str2list(lossObj.value("R1_real").toString());
    QStringList strListR1Imag = global::str2list(lossObj.value("R1_imag").toString());
    QStringList strListWeight = global::str2list(lossObj.value("weight_vswr").toString());
    lossTable->setRowCount(strListR0Real.length());
    for(int i = 0; i < strListR0Real.length(); i++){
        insert2table(lossTable, i, cz0real, strListR0Real[i]);
        insert2table(lossTable, i, cz0imag, strListR0imag[i]);

        QComboBox *lossType = new QComboBox;
        initLossTypeComBox(lossType);
        lossType->setCurrentIndex(QString(strListReturnLossType[i]).toInt());
        lossTable->setCellWidget(i, closstype, lossType);
        //map combobox signal
        connect(lossType, SIGNAL(currentIndexChanged(int)), losssignalsmap, SLOT(map()));
        losssignalsmap->setMapping(lossType, QString("%1-%2").arg(i).arg(closstype));

        QComboBox *optimalType = new QComboBox;
        initOptimalTypeComBox(optimalType);
        optimalType->setCurrentText(strListOptimaltype[i]);
        lossTable->setCellWidget(i, clossoptimaltype, optimalType);
        //map combobox signal
        connect(optimalType, SIGNAL(currentIndexChanged(int)), losssignalsmap, SLOT(map()));
        losssignalsmap->setMapping(optimalType, QString("%1-%2").arg(i).arg(clossoptimaltype));

        insert2table(lossTable, i, cdeltareal, strListDeltaReal[i]);
        insert2table(lossTable, i, cdeltaimag, strListDeltaImag[i]);
        //setting cannot edit when optimize type is delta
        if(2 != optimalType->currentIndex()){
            lossTable->item(i, cdeltareal)->setFlags(Qt::NoItemFlags);
            lossTable->item(i, cdeltaimag)->setFlags(Qt::NoItemFlags);
        }
        if(0 == lossType->currentIndex()){
            //loss type is vswr
            insert2table(lossTable, i, cobjreal, strListVswrobj[i]);
            lossTable->setItem(i, cobjimag, new QTableWidgetItem("None"));
            lossTable->item(i, cobjimag)->setFlags(Qt::NoItemFlags);
        }
        else if(1 == lossType->currentIndex()){
            //loss type is S11
            insert2table(lossTable, i, cobjreal, strListS11[i]);
            lossTable->setItem(i, cobjimag, new QTableWidgetItem("None"));
            lossTable->item(i, cobjimag)->setFlags(Qt::NoItemFlags);
        }
        else if(2 == lossType->currentIndex()){
            //loss type is R
            insert2table(lossTable, i, cobjreal, strListR1Real[i]);
            insert2table(lossTable, i, cobjimag, strListR1Imag[i]);
        }
        else{
            //loss type is None
            lossTable->setItem(i, cobjreal, new QTableWidgetItem("None"));
            lossTable->setItem(i, cobjimag, new QTableWidgetItem("None"));
            lossTable->item(i, cobjreal)->setFlags(Qt::NoItemFlags);
            lossTable->item(i, cobjimag)->setFlags(Qt::NoItemFlags);
        }
        insert2table(lossTable, i, clossweight, strListWeight[i]);
    }
    connect(losssignalsmap, SIGNAL(mapped(QString)), this, SLOT(slot_lossChangeType(QString)));
    return true;
}

void optimizeTab::initOptimalTypeComBox(QComboBox *combox){
    combox->addItem("max");
    combox->addItem("min");
    combox->addItem("delta");
    combox->addItem("None");
    combox->setCurrentIndex(3);
}

void optimizeTab::initLossTypeComBox(QComboBox *combox){
    combox->addItem(tr("驻波比"));
    combox->addItem(tr("S11(dB)"));
    combox->addItem(tr("阻抗"));
    combox->addItem(tr("None"));
    combox->setCurrentIndex(3);
}

void optimizeTab::setSecondTabLayout(){
    QHBoxLayout *gainLayout = new QHBoxLayout;
    gainLayout->addWidget(gainTable);
    groupBoxGain->setLayout(gainLayout);

    QHBoxLayout *axialLayout = new QHBoxLayout;
    axialLayout->addWidget(axialTable);
    groupBoxAxial->setLayout(axialLayout);

    QHBoxLayout *lossLayout = new QHBoxLayout;
    lossLayout->addWidget(lossTable);
    groupBoxLoss->setLayout(lossLayout);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(groupBoxGain);
    vlayout->addWidget(groupBoxAxial);
    vlayout->addWidget(groupBoxLoss);
    secondTab->setLayout(vlayout);
}
//!

//!third tab widget
bool optimizeTab::wizardDialog(){
    varTable->setColumnCount(4);
    QStringList header;
    header << "变量" << "最小值" << "最大值" << "单位";
    varTable->setHorizontalHeaderLabels(header);
    //varTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    varTable->horizontalHeader()->setSectionResizeMode(varnote, QHeaderView::Stretch);
    varTable->horizontalHeader()->setSectionResizeMode(varunit, QHeaderView::ResizeToContents);
    QJsonObject variablesObj = parseJson::getSubJsonObj(obj, "variables");
    if(variablesObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("optimizeTab.cpp:454: error: Cannot parse 'variables' in json file"));
        return false;
    }
    QJsonObject varObj;
    QString varKey;
    QStringList varValue;
    int rownumber = 0, valueListLength;

    //QRegExp rx("^(-?\\d+)(\\.\\d+)?$");
    //QRegExpValidator *floatValid = new QRegExpValidator(rx);      //float
    varTable->setRowCount(variablesObj.count());

    for(QJsonObject::iterator iter = variablesObj.begin(); iter != variablesObj.end(); ++ iter){
        // iter format: "W1":{"note" : "介质板宽度W1(m)", "W1" : "0.025"}
        varKey = iter.key();
        varObj = iter.value().toObject();
        //get note infomation
        QString keyNote = varObj.value("note").toString().trimmed();
        insert2table(varTable, rownumber, varnote, keyNote);
        //setting first column can not edit
        varTable->item(rownumber, varnote)->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        varTable->item(rownumber, varnote)->setWhatsThis(varKey);

        varValue = global::str2list(varObj.value(varKey).toString().trimmed());
        valueListLength = varValue.length();
        insert2table(varTable, rownumber, varmin, varValue[0]);
        if(valueListLength == 1)
            insert2table(varTable, rownumber, varmax, varValue[0]);
        else
            insert2table(varTable, rownumber, varmax, varValue[1]);
        QComboBox *unitComBo = new QComboBox;
        //unitComBo->setFixedWidth(10);
        initUnitComBo(unitComBo);
        varTable->setCellWidget(rownumber, varunit, unitComBo);
        //map combobox signal
        connect(unitComBo, SIGNAL(currentIndexChanged(int)), signalsmap, SLOT(map()));
        signalsmap->setMapping(unitComBo, QString("%1-%2").arg(rownumber).arg(varunit));
        //in 'rownumber'th row of table, save default unitComBo current data
        comboDatas.insert(rownumber, unitComBo->currentData(ROLE_MARK_UNIT).toInt());
        rownumber++;
    }
    connect(signalsmap, SIGNAL(mapped(QString)), this, SLOT(slot_unitchange(QString)));

    //!add picture
    QString picturePath;
    QSqlQuery sqlQuery;
    QString sql = QString("select pModelPath from antennaProblem where pName = '%1';")
            .arg(atnName);
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
    if(pm.width() > 440)
        atnPhoto->setPixmap(pm.scaledToWidth(440));
    else
        atnPhoto->setPixmap(pm);
    //!
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(varTable, 1);
    hLayout->addWidget(atnPhoto, 1);
    thirdTab->setLayout(hLayout);
    return true;
}

double optimizeTab::unitConversion(double sourceData, int preunit, int curunit){
    return sourceData * qPow(10, preunit - curunit);
}

void optimizeTab::initUnitComBo(QComboBox *comb){
    comb->addItem("mm");
    comb->setItemData(0, MARK_UNIT_MM, ROLE_MARK_UNIT);
    comb->addItem("cm");
    comb->setItemData(1, MARK_UNIT_CM, ROLE_MARK_UNIT);
    comb->addItem("λ");
    comb->setItemData(2, MARK_UNIT_LAMBDA, ROLE_MARK_UNIT);
    comb->addItem("m");
    comb->setItemData(3, MARK_UNIT_M, ROLE_MARK_UNIT);
    comb->addItem("km");
    comb->setItemData(4, MARK_UNIT_KM, ROLE_MARK_UNIT);
    comb->setCurrentIndex(3);
}
//!

//!fourth tab widget
void optimizeTab::getConfInfo(){
    generationLine->setText(algObj.value("generation").toString().trimmed());
    popsizeLine->setText(algObj.value("popsize").toString().trimmed());
    threadLine->setText(globalObj.value("ThreadNum").toString().trimmed());
}

void optimizeTab::setAlgComboItem(QString name){
    QString selectProSql = QString(" select a.aId, a.aName "
            " from algorithm as a "
            " inner join algtopro as b on a.aId = b.aId and b.pId = c.pId "
            " inner join antennaProblem as c on c.pName = '%1'; ").arg(name);
    QSqlQuery sqlQuery;
    sqlQuery.prepare(selectProSql);
    if(!sqlQuery.exec(selectProSql)){
        qDebug()<< sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            algCombo->addItem(sqlQuery.value("aName").toString());
        }
    }
}

void optimizeTab::setFourthTabLayout(){
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    //algorithm name
    algLabel->setFixedWidth(80);
    hlayout1->addWidget(algLabel);
    hlayout1->addWidget(algCombo);
    vlayout1->addLayout(hlayout1);

    QGroupBox *algGroup = new QGroupBox();
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    QVBoxLayout *vlayout2 = new QVBoxLayout();
    //generation setting
    generationLabel->setFixedWidth(80);
    hlayout2->addWidget(generationLabel);
    hlayout2->addWidget(generationLine);
    vlayout2->addLayout(hlayout2);
    vlayout2->addSpacing(50);
    //popsize setting
    hlayout2 = new QHBoxLayout();
    popsizeLabel->setFixedWidth(80);
    hlayout2->addWidget(popsizeLabel);
    hlayout2->addWidget(popsizeLine);
    vlayout2->addLayout(hlayout2);
    vlayout2->addSpacing(50);
    //thread number
    hlayout2 = new QHBoxLayout();
    threadLabel->setFixedWidth(80);
    hlayout2->addWidget(threadLabel);
    hlayout2->addWidget(threadLine);
    vlayout2->addLayout(hlayout2);
    algGroup->setLayout(vlayout2);


    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(vlayout1);
    vlayout->addSpacing(50);
    vlayout->addWidget(algGroup);
    vlayout->setContentsMargins(20, 50, 20, 50);

    fourthTab->setLayout(vlayout);
}
//!


void optimizeTab::insert2table(QTableWidget *table, const int &row, const int &clomun, const QString &itemValue){
    QTableWidgetItem *tableItem = new QTableWidgetItem(itemValue);
    tableItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, clomun, tableItem);
}

QJsonObject optimizeTab::saveInJsonObj(){
    QJsonObject saveObj, saveFreObj, saveFarObj, saveGainObj, saveAxialObj, saveLossObj, varObj, saveGlobalObj, saveAlgorithmObj;
    //Frequency Setting json object
    saveFreObj.insert("FreStart", QString("[%1]").arg(freStartEdit->text().trimmed()));
    saveFreObj.insert("FreEnd", QString("[%1]").arg(freEndEdit->text().trimmed()));
    saveFreObj.insert("FreNumber", QString("[%1]").arg(freNumberEdit->text().trimmed()));
    saveFreObj.insert("SweepType", QString("[%1]").arg(sweeptypeComb->currentIndex()));
    saveFreObj.insert("PM", QString("[%1]").arg(PMComb->currentIndex()));

    //Farfield Setting json object
    saveFarObj.insert("ThetaLower", QString("[%1]").arg(thetaStartEdit->text().trimmed()));
    saveFarObj.insert("ThetaUpper", QString("[%1]").arg(thetaEndEdit->text().trimmed()));
    saveFarObj.insert("ThetaStep", QString("[%1]").arg(thetaStepEdit->text().trimmed()));
    saveFarObj.insert("PhiLower", QString("[%1]").arg(phiStartEdit->text().trimmed()));
    saveFarObj.insert("PhiUpper", QString("[%1]").arg(phiEndEdit->text().trimmed()));
    saveFarObj.insert("PhiStep", QString("[%1]").arg(phiStepEdit->text().trimmed()));

    int i;
    //Gain Setting json object
    QStringList gainStr[8];
    for(i = 0; i < gainTable->rowCount(); i++){
        gainStr[0] << gainTable->item(i, cthetalower)->text().trimmed();
        gainStr[1] << gainTable->item(i, cthetaupper)->text().trimmed();
        gainStr[2] << gainTable->item(i, cphilower)->text().trimmed();
        gainStr[3] << gainTable->item(i, cphiupper)->text().trimmed();
        QComboBox *goType = static_cast<QComboBox *>(gainTable->cellWidget(i, coptimaltype));
        if(3 == goType->currentIndex())
            gainStr[4] << goType->currentText().trimmed();
        else
            gainStr[4] << QString("'%1'").arg(goType->currentText().trimmed());
        gainStr[5] << gainTable->item(i, cdelta)->text().trimmed();
        gainStr[6] << gainTable->item(i, cobjvalue)->text().trimmed();
        gainStr[7] << gainTable->item(i, cweight)->text().trimmed();
    }
    saveGainObj.insert("Theta_Lower_gain", QString("[[%1]]").arg(gainStr[0].join(",")));
    saveGainObj.insert("Theta_Upper_gain", QString("[[%1]]").arg(gainStr[1].join(",")));
    saveGainObj.insert("Phi_Lower_gain", QString("[[%1]]").arg(gainStr[2].join(",")));
    saveGainObj.insert("Phi_Upper_gain", QString("[[%1]]").arg(gainStr[3].join(",")));
    saveGainObj.insert("optimaltype_gain", QString("[[%1]]").arg(gainStr[4].join(",")));
    saveGainObj.insert("delta_gain", QString("[[%1]]").arg(gainStr[5].join(",")));
    saveGainObj.insert("gainobj", QString("[[%1]]").arg(gainStr[6].join(",")));
    saveGainObj.insert("weight_gain", QString("[[%1]]").arg(gainStr[7].join(",")));

    //Axial Setting json object
    QStringList axialStr[8];
    for(i = 0; i < axialTable->rowCount(); i++){
        axialStr[0] << axialTable->item(i, cthetalower)->text().trimmed();
        axialStr[1] << axialTable->item(i, cthetaupper)->text().trimmed();
        axialStr[2] << axialTable->item(i, cphilower)->text().trimmed();
        axialStr[3] << axialTable->item(i, cphiupper)->text().trimmed();
        QComboBox *aoType = static_cast<QComboBox *>(axialTable->cellWidget(i, coptimaltype));
        if(3 == aoType->currentIndex())
            axialStr[4] << aoType->currentText().trimmed();
        else
            axialStr[4] << QString("'%1'").arg(aoType->currentText().trimmed());
        axialStr[5] << axialTable->item(i, cdelta)->text().trimmed();
        axialStr[6] << axialTable->item(i, cobjvalue)->text().trimmed();
        axialStr[7] << axialTable->item(i, cweight)->text().trimmed();
    }
    saveAxialObj.insert("Theta_Lower_axial", QString("[[%1]]").arg(axialStr[0].join(",")));
    saveAxialObj.insert("Theta_Upper_axial", QString("[[%1]]").arg(axialStr[1].join(",")));
    saveAxialObj.insert("Phi_Lower_axial", QString("[[%1]]").arg(axialStr[2].join(",")));
    saveAxialObj.insert("Phi_Upper_axial", QString("[[%1]]").arg(axialStr[3].join(",")));
    saveAxialObj.insert("optimaltype_axial", QString("[[%1]]").arg(axialStr[4].join(",")));
    saveAxialObj.insert("delta_axial", QString("[[%1]]").arg(axialStr[5].join(",")));
    saveAxialObj.insert("axialobj", QString("[[%1]]").arg(axialStr[6].join(",")));
    saveAxialObj.insert("weight_axial", QString("[[%1]]").arg(axialStr[7].join(",")));

    //Loss Setting json object
    QStringList lossStr[11];
    for(i = 0; i < lossTable->rowCount(); i++){
        lossStr[0] << lossTable->item(i, cz0real)->text().trimmed();
        lossStr[1] << lossTable->item(i, cz0imag)->text().trimmed();
        QComboBox *lossType = static_cast<QComboBox *>(lossTable->cellWidget(i, closstype));
        lossStr[2] << QString::number(lossType->currentIndex());
        QComboBox *loType = static_cast<QComboBox *>(lossTable->cellWidget(i, clossoptimaltype));
        if(3 == loType->currentIndex())
            lossStr[3] << loType->currentText().trimmed();
        else
            lossStr[3] << QString("'%1'").arg(loType->currentText().trimmed());
        lossStr[4] << lossTable->item(i, cdeltareal)->text().trimmed();
        lossStr[5] << lossTable->item(i, cdeltaimag)->text().trimmed();\
        if(0 == lossType->currentIndex()){
            lossStr[6] << lossTable->item(i, cobjreal)->text().trimmed();
            lossStr[7] << "None";
            lossStr[8] << "None";
        }
        else if(1 == lossType->currentIndex()){
            lossStr[6] << "None";
            lossStr[7] << lossTable->item(i, cobjreal)->text().trimmed();
            lossStr[8] << "None";
        }
        else if(2 == lossType->currentIndex()){
            lossStr[6] << "None";
            lossStr[7] << "None";
            lossStr[8] << lossTable->item(i, cobjreal)->text().trimmed();
        }
        else{
            lossStr[6] << "None";
            lossStr[7] << "None";
            lossStr[8] << "None";
        }
        lossStr[9] << lossTable->item(i, cobjimag)->text().trimmed();
        lossStr[10] << lossTable->item(i, clossweight)->text().trimmed();
    }
    saveLossObj.insert("R0_real", QString("[[%1]]").arg(lossStr[0].join(",")));
    saveLossObj.insert("R0_imag", QString("[[%1]]").arg(lossStr[1].join(",")));
    saveLossObj.insert("ReturnLossType", QString("[[%1]]").arg(lossStr[2].join(",")));
    saveLossObj.insert("optimaltype_vswr", QString("[[%1]]").arg(lossStr[3].join(",")));
    saveLossObj.insert("delta_real", QString("[[%1]]").arg(lossStr[4].join(",")));
    saveLossObj.insert("delta_imag", QString("[[%1]]").arg(lossStr[5].join(",")));
    saveLossObj.insert("vswrobj", QString("[[%1]]").arg(lossStr[6].join(",")));
    saveLossObj.insert("S11", QString("[[%1]]").arg(lossStr[7].join(",")));
    saveLossObj.insert("R1_real", QString("[[%1]]").arg(lossStr[8].join(",")));
    saveLossObj.insert("R1_imag", QString("[[%1]]").arg(lossStr[9].join(",")));
    saveLossObj.insert("weight_vswr", QString("[[%1]]").arg(lossStr[10].join(",")));

    //Variables Setting json object
    QString varKey, varValue, varNote;
    for(int i = 0; i < varTable->rowCount(); i++){
        varKey = varTable->item(i, varnote)->whatsThis().trimmed();
        varNote = varTable->item(i, varnote)->text().trimmed();
        varValue = QString("[%1,%2]").arg(varTable->item(i, varmin)->text().trimmed())
                .arg(varTable->item(i, varmax)->text().trimmed());
        QJsonObject itemobj;
        itemobj.insert("note", varNote);
        itemobj.insert(varKey, varValue);
        varObj.insert(varKey, itemobj);
    }

    //global and algorithm setting
    saveGlobalObj.insert("ThreadNum", threadLine->text().trimmed());
    saveGlobalObj.insert("ALGORITHM_NAME", algName);
    saveGlobalObj.insert("PROBLEM_NAME", atnName);
    saveAlgorithmObj.insert("generation", generationLine->text().trimmed());
    saveAlgorithmObj.insert("popsize", popsizeLine->text().trimmed());

    saveObj.insert("FreSetting", saveFreObj);
    saveObj.insert("ThetaPhiStep", saveFarObj);
    saveObj.insert("GainSetting", saveGainObj);
    saveObj.insert("AxialratioSetting", saveAxialObj);
    saveObj.insert("VSWRSetting", saveLossObj);
    saveObj.insert("variables", varObj);
    saveObj.insert("global", saveGlobalObj);
    saveObj.insert("algorithm", saveAlgorithmObj);
    return saveObj;
}

//slots function
void optimizeTab::slot_gainChangeOptimaltype(QString pos){
    QStringList coordinates = pos.split("-");
    int row = coordinates[0].toInt();
    int col = coordinates[1].toInt();
    QComboBox *selectCombox = (QComboBox *)gainTable->cellWidget(row, col);
    //setting edit when optimize type is delta
    if(selectCombox->currentIndex() == 2)
        gainTable->item(row, cdelta)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    else
        gainTable->item(row, cdelta)->setFlags(Qt::NoItemFlags);
}

void optimizeTab::slot_axialChangeOptimaltype(QString pos){
    QStringList coordinates = pos.split("-");
    int row = coordinates[0].toInt();
    int col = coordinates[1].toInt();
    QComboBox *selectCombox = (QComboBox *)axialTable->cellWidget(row, col);
    //setting edit when optimize type is delta
    if(selectCombox->currentIndex() == 2){
        qDebug() << selectCombox->currentIndex();
        axialTable->item(row, cdelta)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    }
    else
        axialTable->item(row, cdelta)->setFlags(Qt::NoItemFlags);
}

void optimizeTab::slot_lossChangeType(QString pos){
    QStringList coordinates = pos.split("-");
    int row = coordinates[0].toInt();
    int col = coordinates[1].toInt();
    QComboBox *selectCombox = (QComboBox *)lossTable->cellWidget(row, col);
    //setting edit when optimize type is delta
    if(col == clossoptimaltype){
        if(2 == selectCombox->currentIndex()){
            lossTable->item(row, cdeltareal)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
            lossTable->item(row, cdeltaimag)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        }
        else{
            lossTable->item(row, cdeltareal)->setFlags(Qt::NoItemFlags);
            lossTable->item(row, cdeltaimag)->setFlags(Qt::NoItemFlags);
        }
    }
    if(col == closstype){
        if(2 == selectCombox->currentIndex())
            lossTable->item(row, cobjimag)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
        else
            lossTable->item(row, cobjimag)->setFlags(Qt::NoItemFlags);
    }
}

void optimizeTab::slot_unitchange(QString pos){
    Q_ASSERT(!comboDatas.isEmpty());
    QStringList coordinates = pos.split("-");
    int row = coordinates.at(0).toInt();
    int col = coordinates.at(1).toInt();
    int currentUnitData = comboDatas[row];
    QComboBox *selectCombox = (QComboBox *)varTable->cellWidget(row, col);
    qDebug() << selectCombox->currentText();
    int newUnitData = selectCombox->currentData(ROLE_MARK_UNIT).toInt();
    //qDebug() << varTable->item(row, varnote)->whatsThis();
    if(currentUnitData != MARK_UNIT_LAMBDA && newUnitData != MARK_UNIT_LAMBDA &&
            newUnitData != currentUnitData){
        double preValueMin = varTable->item(row, varmin)->text().trimmed().toDouble();
        double preValueMax = varTable->item(row, varmax)->text().trimmed().toDouble();
        double currentValueMin = unitConversion(preValueMin, currentUnitData, newUnitData);
        double currentValueMax = unitConversion(preValueMax, currentUnitData, newUnitData);
        qDebug() << currentValueMin << currentValueMax;
        insert2table(varTable, row, varmin, QString::number(currentValueMin));
        insert2table(varTable, row, varmax, QString::number(currentValueMax));
    }
    comboDatas[row] = newUnitData;
}

void optimizeTab::slot_algName(const int index){
    algName = algCombo->itemText(index);
    getConfInfo();
}

void optimizeTab::slot_saveAllButton(bool){
    bool isOK = true;
    QJsonObject newObj = saveInJsonObj();
    QJsonObject freObj = parseJson::getSubJsonObj(newObj, "FreSetting");
    QJsonObject farObj = parseJson::getSubJsonObj(newObj, "ThetaPhiStep");
    QJsonObject gainObj = parseJson::getSubJsonObj(newObj, "GainSetting");
    QJsonObject axialObj = parseJson::getSubJsonObj(newObj, "AxialratioSetting");
    QJsonObject lossObj = parseJson::getSubJsonObj(newObj, "VSWRSetting");
    QJsonObject varsObj = parseJson::getSubJsonObj(newObj, "variables");
    QJsonObject globalObj = parseJson::getSubJsonObj(newObj, "global");
    QJsonObject algorithmObj = parseJson::getSubJsonObj(newObj, "algorithm");
    if(freObj.isEmpty() || farObj.isEmpty() || gainObj.isEmpty() || axialObj.isEmpty() ||
            lossObj.isEmpty() || varsObj.isEmpty() || globalObj.isEmpty() || algorithmObj.isEmpty())
        isOK = false;
    else{
        obj.insert("FreSetting", freObj);
        obj.insert("ThetaPhiStep", farObj);
        obj.insert("GainSetting", gainObj);
        obj.insert("AxialratioSetting", axialObj);
        obj.insert("VSWRSetting", lossObj);
        obj.insert("variables", varsObj);
        QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentOptimizePath"]).arg(atnName);
        QString globalJsonPath = QString("%1/global_conf.json").arg(sysParam["CurrentOptimizePath"]);
        QString algorithmJsonPath = QString("%1/algorithm_conf.json").arg(sysParam["CurrentOptimizePath"]);
        if(! (parseJson::write(jsonPath, obj)
              && parseJson::write(globalJsonPath, globalObj)
              && parseJson::write(algorithmJsonPath, algorithmObj)) )
            isOK = false;
    }
    if(isOK){
        this->close();
    }
    else
        QMessageBox::critical(0, QString("Error"), QString("optimizeTab.cpp:851: error: Cannot update in json file"));
}
