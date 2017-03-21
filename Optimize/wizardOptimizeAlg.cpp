#include "wizardOptimizeAlg.h"

wizardOptimizeAlg::wizardOptimizeAlg(QWidget *parent) : QWizardPage(parent){
    setTitle(tr("优化算法设置"));
    setSubTitle(tr("设置算法参数"));
    this->varTable = new QTableWidget();
    this->atnName = global::getInfoFromRel("Problem");
    this->algLabel = new QLabel(tr("选择算法:"));
    this->algCombo = new QComboBox();

    this->singleComp = new QCheckBox();
    this->singleComp->setText(QString("单机计算"));
    this->singleComp->setCheckState(Qt::Checked);
    this->threadLabel = new QLabel(tr("启动核数"));
    this->threadLine = new QLineEdit();

    this->multiComp = new QCheckBox();
    this->multiComp->setText(QString("多机计算"));
    this->multiComp->setCheckState(Qt::Unchecked);
    this->nodeLabel = new QLabel(QString("node"));
    this->coreLabel = new QLabel(QString("cores"));
    this->nodeEdit = new QLineEdit();
    this->coreEdit = new QLineEdit();
    this->nodesTable = new QTableWidget();
    this->addButton = new QPushButton(QString("添加"));
    this->delButton = new QPushButton(QString("删除"));

    this->singleGroup = new QGroupBox();
    this->multiGroup = new QGroupBox();

    this->hint = new QLabel();

    this->proPath = setPath(atnName, proPy);
    setAlgComboItem(atnName);
    algCombo->setCurrentIndex(0);
    this->algName = algCombo->currentText().trimmed();
    this->algPath = setPath(algName, algPy);

    varTable->setColumnCount(2);
    varTable->horizontalHeader()->setVisible(false);
    varTable->horizontalHeader()->setSectionResizeMode(valueFlag, QHeaderView::Stretch);
    varTable->verticalHeader()->setVisible(false);
    varTable->setFrameShape(QFrame::NoFrame);                   //setting no frame
    varTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    varTable->setSelectionMode(QAbstractItemView::SingleSelection);     //select signal row every time
    varTable->setStyleSheet("selection-background-color:lightblue;");   //setting selected background

    nodesTable->setColumnCount(2);
    QStringList header;
    header << "IP地址/主机名" << "启动核数";
    nodesTable->setHorizontalHeaderLabels(header);
    nodesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //nodesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    nodesTable->verticalHeader()->setVisible(false);

    nodesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    nodesTable->setSelectionMode(QAbstractItemView::SingleSelection);     //select signal row every time
    nodesTable->setStyleSheet("selection-background-color:lightblue;");   //setting selected background

    //get thread num from global_conf.json
    QString DEA4ADglobalPath = QString("./DEA4AD/trunk");
    QString globalJsonPath = QString("%1/global_conf.json").arg(DEA4ADglobalPath);
    QJsonObject globalObj = parseJson::getJsonObj(globalJsonPath);
    threadLine->setText(QString::number(globalObj.value("ThreadNum").toString().trimmed().toInt()-1));

    confSetting();
    initLayout();
    connect(singleComp, SIGNAL(stateChanged(int)), this, SLOT(slot_singleCheckBoxStateChange(int)));
    connect(multiComp, SIGNAL(stateChanged(int)), this, SLOT(slot_multiCheckBoxStateChange(int)));
    connect(algCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_algName(int)));
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(slot_addNodeButton()));
    connect(delButton, SIGNAL(clicked(bool)), this, SLOT(slot_delNodeButton()));
}

void wizardOptimizeAlg::confSetting(){
    QString algConfJaonPath = QString("%1/%2_conf.json").arg(algPath).arg(algName);
    QJsonObject algObj = parseJson::getJsonObj(algConfJaonPath);
    if(algObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardOptimizeAlg.cpp:38: error: Cannot parse 'algObj' in json file"));
        return;
    }
    varTable->setRowCount(algObj.count());
    QString varKey, varValue, valueNote;
    QJsonObject varObj; //format:{"generation": "1000", "note": "最大代数", "instruction": "最大迭代次数"}
    int rownumber = 0;

    for(QJsonObject::iterator iter = algObj.begin(); iter != algObj.end(); ++ iter){
        varKey = iter.key();
        varObj = iter.value().toObject();
        varValue = varObj.value(varKey).toString().trimmed();
        valueNote = varObj.value("note").toString().trimmed();        
        //valueInstruction = varObj.value("instruction").toString().trimmed();

        insert2table(varTable, rownumber, keyFlag, valueNote);
        QTableWidgetItem *flagItem = varTable->item(rownumber, keyFlag);
        flagItem->setWhatsThis(varKey);
        //set this column cannot edit
        flagItem->setFlags(flagItem->flags() & (~Qt::ItemIsEditable));
        insert2table(varTable, rownumber, valueFlag, varValue);
        rownumber ++;
    }
}

void wizardOptimizeAlg::initLayout(){    
    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();
    QHBoxLayout *hlayoutTemp = new QHBoxLayout();
    QVBoxLayout *vlayoutTemp = new QVBoxLayout();
    QGroupBox *lgroup = new QGroupBox(QString("算法参数设置"));
    QGroupBox *rgroup = new QGroupBox(QString("分布式并行"));

    //algorithm name
    algLabel->setFixedWidth(80);
    hlayoutTemp->addWidget(algLabel);
    hlayoutTemp->addWidget(algCombo);
    vlayout->addLayout(hlayoutTemp);


    //new hlayoutTemp
    hlayoutTemp = new QHBoxLayout();
    hlayoutTemp->addWidget(varTable);
    lgroup->setLayout(hlayoutTemp);

    //thread number
    //new hlayoutTemp
    hlayoutTemp = new QHBoxLayout();
    threadLabel->setFixedWidth(80);
    hlayoutTemp->addWidget(threadLabel);
    hlayoutTemp->addWidget(threadLine);

    singleGroup->setLayout(hlayoutTemp);    

    //new hlayoutTemp
    hlayoutTemp = new QHBoxLayout();
    hlayoutTemp->addWidget(nodeLabel);
    hlayoutTemp->addWidget(nodeEdit);
    hlayoutTemp->addWidget(coreLabel);
    hlayoutTemp->addWidget(coreEdit);
    hlayoutTemp->addWidget(addButton);
    vlayoutTemp->addLayout(hlayoutTemp);

    //new hlayoutTemp
    hlayoutTemp = new QHBoxLayout();
    hlayoutTemp->addWidget(nodesTable);
    hlayoutTemp->addWidget(delButton);
    vlayoutTemp->addLayout(hlayoutTemp);
    multiGroup->setLayout(vlayoutTemp);

    singleGroup->setEnabled(true);
    multiGroup->setEnabled(false);
    //new vlayoutTemp
    vlayoutTemp = new QVBoxLayout();
    vlayoutTemp->addWidget(singleComp);
    vlayoutTemp->addWidget(singleGroup);
    vlayoutTemp->addWidget(multiComp);
    vlayoutTemp->addWidget(multiGroup);


    rgroup->setLayout(vlayoutTemp);
    hlayout->addWidget(lgroup);
    hlayout->addWidget(rgroup);

    //hint
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hint->setAlignment(Qt::AlignRight);
    hlayout2->addWidget(hint);

    vlayout->addSpacing(20);
    vlayout->addLayout(hlayout);
    vlayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vlayout->addLayout(hlayout2);

    vlayout->setContentsMargins(20, 10, 20, 10);
    setLayout(vlayout);
}

void wizardOptimizeAlg::setAlgComboItem(QString name){
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

QString wizardOptimizeAlg::setPath(QString name, bool flag){
    QString pyPath;
    QString getPySql;
    QString pyFlag;
    if(flag == 0){
        getPySql = QString("select proPath from antennaProblem where pName = '%1';").arg(name);
        pyFlag = "proPath";
    }
    else{
        getPySql = QString("select algPath from algorithm where aName = '%1';").arg(name);
        pyFlag = "algPath";
    }
    QSqlQuery sqlQuery;
    sqlQuery.prepare(getPySql);
    if(!sqlQuery.exec(getPySql)){
        qDebug()<< sqlQuery.lastError();
    }
    else{
        while(sqlQuery.next()){
            pyPath = sqlQuery.value(pyFlag).toString();
        }
    }
    return pyPath;
}

QString wizardOptimizeAlg::getProPath() const{
    return proPath;
}

QString wizardOptimizeAlg::getAlgPath() const{
    return algPath;
}

QString wizardOptimizeAlg::getAlgName() const{
    return algName;
}

QJsonObject wizardOptimizeAlg::saveInJsonObj(){
    QJsonObject saveObj, globalObj, algObj, nodeAndThreadObj;
    QString strNumber = threadLine->text().trimmed();
    int intNumber = 0;
    if(strNumber != NULL)
        intNumber = strNumber.toInt();
    globalObj.insert("ThreadNum", QString::number(intNumber+1));
    globalObj.insert("ALGORITHM_NAME", algName);
    globalObj.insert("PROBLEM_NAME", atnName);
    saveObj.insert("global", globalObj);

    QString varKey, varValue, varNote;
    for(int i = 0; i < varTable->rowCount(); ++i){
        varKey = varTable->item(i, keyFlag)->whatsThis().trimmed();
        varNote = varTable->item(i, keyFlag)->text().trimmed();
        varValue = QString("%1").arg(varTable->item(i, valueFlag)->text().trimmed());
        QJsonObject itemobj;
        itemobj.insert(varKey, varValue);
        itemobj.insert("note", varNote);
        algObj.insert(varKey, itemobj);
    }
    saveObj.insert("algorithm", algObj);

    for(int i = 0; i < nodesTable->rowCount(); ++ i){
        QString nodeOrIp, core, strUID;
        QJsonObject ncitemobj;
        strUID = QUuid::createUuid().toString();
        nodeOrIp = nodesTable->item(i, nodeFlag)->text().trimmed();
        core = nodesTable->item(i, coreFlag)->text().trimmed();
        ncitemobj.insert("node", nodeOrIp);
        ncitemobj.insert("threads", core);
        nodeAndThreadObj.insert(strUID, ncitemobj);
    }
    saveObj.insert("NodeAndThread", nodeAndThreadObj);

    return saveObj;
}

bool wizardOptimizeAlg::validatePage(){
    if (algCombo->currentIndex() == -1){
        hint->setStyleSheet("font-color:red");
        hint->setText("请选择算法！");
        return false;
    }
    return true;
}

void wizardOptimizeAlg::insert2table(QTableWidget *table, const int &row, const int &clomun, const QString &itemValue){
    QTableWidgetItem *tableItem = new QTableWidgetItem(itemValue);
    tableItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, clomun, tableItem);
}

//signals function
void wizardOptimizeAlg::slot_algName(const int index){
    algName = algCombo->itemText(index);
    algPath = setPath(algName, algPy);
    confSetting();
}

void wizardOptimizeAlg::slot_singleCheckBoxStateChange(const int state){
    //state: enum explain{Qt::Unchecked=0, Qt::PartiallyChecked, Qt::Checked}
    //so usually using 0(unchecked), 2(checked);
    //qDebug() << state;
    if(state == 0){
        singleGroup->setEnabled(false);
        multiComp->setCheckState(Qt::Checked);
    }
    else if(state == 2){
        //set another checkBox(multiCheckBox unChecked)
        singleGroup->setEnabled(true);
        multiComp->setCheckState(Qt::Unchecked);
    }
}

void wizardOptimizeAlg::slot_multiCheckBoxStateChange(const int state){
    if(state == 0){
        //set another checkBox(multiCheckBox Checked)
        multiGroup->setEnabled(false);
        singleComp->setCheckState(Qt::Checked);
    }
    else if(state == 2){
        //set another checkBox(multiCheckBox unChecked)
        multiGroup->setEnabled(true);
        singleComp->setCheckState(Qt::Unchecked);
    }
}

void wizardOptimizeAlg::slot_addNodeButton(){
    QString nodeinfo, coreinfo;
    int rowIndex = nodesTable->rowCount();
    //qDebug() << rowIndex;
    nodesTable->insertRow(rowIndex);
    nodeinfo = nodeEdit->text().trimmed();
    coreinfo = coreEdit->text().trimmed();
    insert2table(nodesTable, rowIndex, nodeFlag, nodeinfo);
    insert2table(nodesTable, rowIndex, coreFlag, coreinfo);
}

void wizardOptimizeAlg::slot_delNodeButton(){
    int selectRow = nodesTable->currentRow();
    //qDebug() << selectRow;
    if(selectRow != -1)
        nodesTable->removeRow(selectRow);
}
