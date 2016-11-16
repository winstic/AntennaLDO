#include "wizardOptimizeGainAxialLoss.h"

wizardOptimizeAXL::wizardOptimizeAXL(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    setTitle(tr("增益轴比回波损失设置"));
    setSubTitle(tr("设置增益轴比回波损失等参数"));
    this->obj = obj;
    this->groupBoxGain = new QGroupBox(tr("增益设置"));
    this->groupBoxAxial = new QGroupBox(tr("轴比设置"));
    this->groupBoxLoss = new QGroupBox(tr("回波损失"));
    this->gainTable = new QTableWidget();
    this->axialTable = new QTableWidget();
    this->lossTable = new QTableWidget();
    this->gainsignalsmap = new QSignalMapper();
    this->axialsignalsmap = new QSignalMapper();
    this->losssignalsmap = new QSignalMapper();

    gainSetting();
    axialSetting();
    lossSetting();
    initLayout();
}

bool wizardOptimizeAXL::gainSetting(){
    gainTable->setColumnCount(8);
    QStringList header;
    header << "起始θ" << "终止θ" << "起始φ" << "终止φ" << "优化方式" << "误差值" << "增益(dB)" << "权值";
    gainTable->setHorizontalHeaderLabels(header);
    //gainTable->setStyleSheet("QTableView {selection-background-color: grey;}");
    gainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //qDebug() << gainTable->width();
    QJsonObject gainObj = parseJson::getSubJsonObj(obj, "GainSetting");
    if(gainObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardOptimizeAXL.cpp:34: error: Cannot parse 'GainSetting' in json file"));
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

bool wizardOptimizeAXL::axialSetting(){
    axialTable->setColumnCount(8);
    QStringList header;
    header << "起始θ" << "终止θ" << "起始φ" << "终止φ" << "优化方式" << "误差值" << "轴比(dB)" << "权值";
    axialTable->setHorizontalHeaderLabels(header);
    axialTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonObject axialObj = parseJson::getSubJsonObj(obj, "AxialratioSetting");
    if(axialObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardOptimizeAXL.cpp:60: error: Cannot parse 'AxialratioSetting' in json file"));
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

bool wizardOptimizeAXL::lossSetting(){
    lossTable->setColumnCount(9);
    QStringList header;
    header << "Z0实部" << "Z0虚部" << "损失方式" << "优化方式" << "误差实部" << "误差虚部" << "值实部" << "值虚部" << "权值";
    lossTable->setHorizontalHeaderLabels(header);
    lossTable->resizeColumnToContents(6);
    lossTable->resizeColumnToContents(7);
    lossTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonObject lossObj = parseJson::getSubJsonObj(obj, "VSWRSetting");
    if(lossObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardOptimizeAXL.cpp:86: error: Cannot parse 'VSWRSetting' in json file"));
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

void wizardOptimizeAXL::initOptimalTypeComBox(QComboBox *combox){
    combox->addItem("max");
    combox->addItem("min");
    combox->addItem("delta");
    combox->addItem("None");
    combox->setCurrentIndex(3);    
}

void wizardOptimizeAXL::initLossTypeComBox(QComboBox *combox){
    combox->addItem(tr("驻波比"));
    combox->addItem(tr("S11(dB)"));
    combox->addItem(tr("阻抗"));
    combox->addItem(tr("None"));
    combox->setCurrentIndex(3);
}

void wizardOptimizeAXL::initLayout(){
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
    setLayout(vlayout);
}

void wizardOptimizeAXL::insert2table(QTableWidget *table, const int &row, const int &clomun, const QString &itemValue){
    QTableWidgetItem *tableItem = new QTableWidgetItem(itemValue);
    tableItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, clomun, tableItem);
}

bool wizardOptimizeAXL::validatePage(){
    return true;
}

QJsonObject wizardOptimizeAXL::saveInJsonObj(){
    QJsonObject saveObj, saveGainObj, saveAxialObj, saveLossObj;
    int i;
    //save gain setting
    QStringList gainStr[8];
    for(i = 0; i < gainTable->rowCount(); i++){
        gainStr[0] << gainTable->item(i, cthetalower)->text().trimmed();
        gainStr[1] << gainTable->item(i, cthetaupper)->text().trimmed();
        gainStr[2] << gainTable->item(i, cphilower)->text().trimmed();
        gainStr[3] << gainTable->item(i, cphiupper)->text().trimmed();
        gainStr[4] << static_cast<QComboBox *>(gainTable->cellWidget(i, coptimaltype))->currentText().trimmed();
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

    //save axial setting
    QStringList axialStr[8];
    for(i = 0; i < axialTable->rowCount(); i++){
        axialStr[0] << axialTable->item(i, cthetalower)->text().trimmed();
        axialStr[1] << axialTable->item(i, cthetaupper)->text().trimmed();
        axialStr[2] << axialTable->item(i, cphilower)->text().trimmed();
        axialStr[3] << axialTable->item(i, cphiupper)->text().trimmed();
        axialStr[4] << static_cast<QComboBox *>(axialTable->cellWidget(i, coptimaltype))->currentText().trimmed();
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

    //save loss setting
    QStringList lossStr[11];
    for(i = 0; i < lossTable->rowCount(); i++){
        lossStr[0] << lossTable->item(i, cz0real)->text().trimmed();
        lossStr[1] << lossTable->item(i, cz0imag)->text().trimmed();
        QComboBox *lossType = static_cast<QComboBox *>(lossTable->cellWidget(i, closstype));
        lossStr[2] << lossType->currentText().trimmed();
        lossStr[3] << static_cast<QComboBox *>(lossTable->cellWidget(i, clossoptimaltype))->currentText().trimmed();
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


    saveObj.insert("GainSetting", saveGainObj);
    saveObj.insert("AxialratioSetting", saveAxialObj);
    saveObj.insert("VSWRSetting", saveLossObj);
    return saveObj;
}

//slots function
void wizardOptimizeAXL::slot_gainChangeOptimaltype(QString pos){
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

void wizardOptimizeAXL::slot_axialChangeOptimaltype(QString pos){
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

void wizardOptimizeAXL::slot_lossChangeType(QString pos){
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

