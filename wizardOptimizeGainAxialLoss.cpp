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
        if(optimalType->currentIndex() != 2){
            lossTable->item(i, cdeltareal)->setFlags(Qt::NoItemFlags);
            lossTable->item(i, cdeltaimag)->setFlags(Qt::NoItemFlags);
        }
        if(lossType->currentIndex() == 0){
            //loss type is vswr
            insert2table(lossTable, i, cobjreal, strListVswrobj[i]);
            lossTable->setItem(i, cobjimag, new QTableWidgetItem(""));
            lossTable->item(i, cobjimag)->setFlags(Qt::NoItemFlags);
        }
        else if(lossType->currentIndex() == 1){
            //loss type is S11
            insert2table(lossTable, i, cobjreal, strListS11[i]);
            lossTable->setItem(i, cobjimag, new QTableWidgetItem(""));
            lossTable->item(i, cobjimag)->setFlags(Qt::NoItemFlags);
        }
        else if(lossType->currentIndex() == 2){
            //loss type is R
            insert2table(lossTable, i, cobjreal, strListR1Real[i]);
            insert2table(lossTable, i, cobjimag, strListR1Imag[i]);
        }
        else{
            //loss type is None
            lossTable->setItem(i, cobjreal, new QTableWidgetItem(""));
            lossTable->setItem(i, cobjimag, new QTableWidgetItem(""));
            lossTable->item(i, cobjreal)->setFlags(Qt::NoItemFlags);
            lossTable->item(i, cobjimag)->setFlags(Qt::NoItemFlags);
        }
        insert2table(lossTable, i, clossweight, strListWeight[i]);        
    }
    connect(losssignalsmap, SIGNAL(mapped(QString)), this, SLOT(slot_lossChangeType(QString)));
    return true;
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

