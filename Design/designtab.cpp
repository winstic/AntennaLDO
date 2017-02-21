#include "designtab.h"

designTab::designTab(QJsonObject obj, QWidget *parent) : QDialog(parent){
    this->obj = obj;
    this->tabWidget = new QTabWidget();
    this->setMinimumSize(880, 580);
    //remove help menu
    this->setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    this->firstTab = new QWidget(this);
    this->secondTab = new QWidget(this);
    this->saveAllButton = new QPushButton("保存所有");
    connect(saveAllButton, SIGNAL(clicked(bool)), this, SLOT(slot_saveAllButton(bool)));

    //!first tabwidget
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
    initSetupCom();
    frequencySetting();
    farFieldSetting();
    setFirstTabLayout();
    //!

    //!second tab widget
    this->varTable = new QTableWidget();
    this->signalsmapSlider = new QSignalMapper();
    this->signalsmapUnit = new QSignalMapper();
    tableSetting();
    readDefaultVars();
    variablesSetting();
    //!
    tabWidget->addTab(firstTab, QIcon(""), tr("性能参数设置"));
    //firstTab->setWindowTitle(tr("设置频率信息并指定远场范围"));
    tabWidget->addTab(secondTab, QIcon(""), tr("模型设置"));
    //secondTab->setWindowTitle(tr("模型设置"));
    //QScrollArea *scrollArea = new QScrollArea;
    //scrollArea->setWidget(tabWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    buttonLayout->addWidget(saveAllButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tabWidget);
    layout->addLayout(buttonLayout);

    this->setWindowTitle(tr("天线设计"));    
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
    layout->addWidget(groupBoxFrequency);
    layout->addWidget(groupBoxFarField);
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->setSpacing(100);
    layout->setContentsMargins(2,50,2,50);
    firstTab->setLayout(layout);
    //!
}
//!

//!sceond widget
void designTab::tableSetting(){
    varTable->setColumnCount(3);
    QStringList header;
    header << "变量" << "参数值" << "单位";
    varTable->setHorizontalHeaderLabels(header);
    varTable->horizontalHeader()->setSectionsClickable(false);
    varTable->horizontalHeader()->setSectionResizeMode(varvalue, QHeaderView::Stretch);
    varTable->horizontalHeader()->setSectionResizeMode(varunit, QHeaderView::ResizeToContents);
    varTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //varTable->verticalHeader()->setDefaultSectionSize(0);      //setting row spacing
    varTable->setFrameShape(QFrame::NoFrame);                   //setting no frame
    varTable->setShowGrid(false);                               //setting no grid line
    varTable->verticalHeader()->setVisible(false);              //setting no vertical header
    varTable->horizontalHeader()->resizeSection(0, 120);        //setting first column width is 150
    varTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    varTable->setSelectionMode(QAbstractItemView::SingleSelection);     //select signal row every time
    varTable->setStyleSheet("selection-background-color:lightblue;");   //setting selected background
    varTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //setting header background
    varTable->setEditTriggers(QAbstractItemView::NoEditTriggers);       //no edit
}

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

void designTab::initUnitComBo(QComboBox* comb){
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

bool designTab::variablesSetting(){
    QJsonObject variablesObj = parseJson::getSubJsonObj(obj, "variables");
    if(variablesObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardDesignVariables.cpp:27: error: Cannot parse 'variables' in json file"));
        return false;
    }
    QJsonObject varObj;
    QString varKey;
    QStringList varValue;
    int rownumber = 0, valueListLength;
    double realValue;

    QRegExp rx("^(-?\\d+)(\\.\\d+)?$");
    QRegExpValidator *floatValid = new QRegExpValidator(rx);      //float
    varTable->setRowCount(variablesObj.count());

    for(QJsonObject::iterator iter = variablesObj.begin(); iter != variablesObj.end(); ++ iter){
        // iter format: "W1":{"note" : "介质板宽度W1(m)", "W1" : "0.025"}
        varKey = iter.key();
        varObj = iter.value().toObject();   //like {"note": "上贴片坐标y1(m)", "y1": "[-0.0115,0]"}
        //get note infomation
        QString keyNote = varObj.value("note").toString().trimmed();
        insert2table(rownumber, varnote, keyNote);
        varTable->item(rownumber, varnote)->setWhatsThis(varKey);
        //varTable->item(rownumber, varnote)->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);

        // init line edit and layout
        varValue = global::str2list(varObj.value(varKey).toString().trimmed());
        valueListLength = varValue.length();
        QLineEdit *valueEdit = new QLineEdit;
        //valueEdit->setFixedWidth(240);
        valueEdit->setValidator(floatValid);

        if(valueListLength == 1){
            valueEdit->setText(varValue[0]);
            valueEdit->setReadOnly(true);
            varTable->setCellWidget(rownumber, varvalue, valueEdit);
        }
        else{
            QWidget *cellWidget = new QWidget();
            QVBoxLayout *vLayout = new QVBoxLayout;
            QSlider *varSlider = new QSlider(Qt::Horizontal);

            varSlider->setStyleSheet(getSliderSheet());
            varSlider->setMinimum(0);
            varSlider->setMaximum(100);
            varSlider->setSingleStep(1);

            double stopValue = QString(varValue[1]).trimmed().toDouble();
            double startValue = QString(varValue[0]).trimmed().toDouble();
            realValue = defaultVars[varKey].trimmed().toDouble();
            if(stopValue == startValue){
                varSlider->setValue(100);
                varSlider->setEnabled(false);
            }
            else{
                int sliderValue = 100 * (realValue - startValue) / (stopValue - startValue);
                varSlider->setValue(sliderValue);
            }
            //!conversion slider value and edit value
            valueEdit->setText(QString::number(realValue));


            //valueEdit->setReadOnly(true);
            vLayout->addWidget(valueEdit);
            vLayout->addWidget(varSlider);
            //design inner space
            vLayout->setSpacing(0);
            // design outer space
            //vLayout->setMargin(0);
            cellWidget->setLayout(vLayout);
            //test begin
            //QLineEdit *findEdit = cellWidget->findChild<QLineEdit *>();
            //qDebug() << "findEdit: " << findEdit->text();
            //test end
            varTable->setCellWidget(rownumber, varvalue, cellWidget);

            connect(varSlider, SIGNAL(valueChanged(int)), signalsmapSlider, SLOT(map()));
            signalsmapSlider->setMapping(varSlider, QString("%1#%2#%3").arg(rownumber).arg(stopValue).arg(startValue));
        }
        //connect(valueEdit, SIGNAL(textChanged(QString)), this, SLOT(slot_LinetextChange(QString)));
        //valueEdit->installEventFilter(this);        //install filter in this dialog(在对话框上为QLineEdit安装过滤器)
        QWidget *unitWidget = new QWidget();
        QHBoxLayout *unitLayout = new QHBoxLayout();
        QComboBox *unitComBo = new QComboBox();
        unitComBo->setFixedHeight(25);
        initUnitComBo(unitComBo);
        unitLayout->addWidget(unitComBo);
        unitWidget->setLayout(unitLayout);
        varTable->setCellWidget(rownumber, varunit, unitWidget);

        //map combobox signal
        connect(unitComBo, SIGNAL(currentIndexChanged(int)), signalsmapUnit, SLOT(map()));
        signalsmapUnit->setMapping(unitComBo, QString("%1").arg(rownumber));
        //in 'rownumber'th row, save default unitComBo current data
        comboDatas.insert(rownumber, unitComBo->currentData(ROLE_MARK_UNIT).toInt());
        rownumber++;
    }

    connect(signalsmapSlider, SIGNAL(mapped(QString)), this, SLOT(slot_sliderValueChange(QString)));
    connect(signalsmapUnit, SIGNAL(mapped(QString)), this, SLOT(slot_unitchange(QString)));

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
    if(pm.width() > 440)
        atnPhoto->setPixmap(pm.scaledToWidth(440));
    else
        atnPhoto->setPixmap(pm);
    //!
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(varTable, 1);
    hLayout->addWidget(atnPhoto, 1);

    secondTab->setLayout(hLayout);
    return true;
}

QString designTab::getSliderSheet(){
    return QString("  \
         QSlider\
         {     \
            spacing: 0px;\
            min-height:8px;\
            max-height:8px;\
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

QJsonObject designTab::saveInJsonObj(){
    QJsonObject saveObj, saveFreObj, saveFarObj, varObj;

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

    //Variables Setting json object
    QString varKey, varValue;
    for(int i = 0; i < varTable->rowCount(); i++){
        varKey = varTable->item(i, varnote)->whatsThis().trimmed();
        varValue = varTable->cellWidget(i, varvalue)->findChild<QLineEdit *>()->text().trimmed();
        varObj.insert(varKey, varValue);
    }

    saveObj.insert("FreSetting", saveFreObj);
    saveObj.insert("ThetaPhiStep", saveFarObj);
    saveObj.insert("varsValue", varObj);
    return saveObj;
}

void designTab::insert2table(const int &row, const int &clomun, const QString &itemValue){
    QTableWidgetItem *tableItem = new QTableWidgetItem(itemValue);
    tableItem->setTextAlignment(Qt::AlignCenter);
    varTable->setItem(row, clomun, tableItem);
}

double designTab::unitConversion(double sourceData, int preunit, int curunit){
    //assert(preunit != unitlambda && curunit != unitlambda);
    return sourceData * qPow(10, preunit - curunit);
}

//slots function
void designTab::slot_LinetextChange(QString text){
    //qDebug() << text;
}

void designTab::slot_sliderValueChange(QString sparameter){
    QStringList parameterList = sparameter.split("#");
    int rowNumber = parameterList.at(0).toInt();        //table rowth
    double upper = parameterList.at(1).toDouble();
    double lower = parameterList.at(2).toDouble();
    //get widget
    QSlider* selectSlider = varTable->cellWidget(rowNumber, varvalue)->findChild<QSlider *>();
    QLineEdit* selectLineEdit = varTable->cellWidget(rowNumber, varvalue)->findChild<QLineEdit *>();
    int svalue = selectSlider->value();
    double levalue = selectLineEdit->text().trimmed().toDouble();
    //get new edit value by slider value
    double newLineEditValue = (upper - lower)/100.0 * svalue + lower;
    selectLineEdit->setText(QString::number(newLineEditValue));
}

void designTab::slot_unitchange(QString pos){
    Q_ASSERT(!comboDatas.isEmpty());
    int row = pos.toInt();
    int currentUnitData = comboDatas[row];
    QComboBox *selectCombox = varTable->cellWidget(row, varunit)->findChild<QComboBox *>();
    //qDebug() << selectCombox->currentText();
    int newUnitData = selectCombox->currentData(ROLE_MARK_UNIT).toInt();
    //qDebug() << currentUnitData << newUnitData;
    //unit conversion
    if(currentUnitData != MARK_UNIT_LAMBDA && newUnitData != MARK_UNIT_LAMBDA &&
            newUnitData != currentUnitData){
        //get QLineEdit widget
        QLineEdit* currLineEdit = varTable->cellWidget(row, varvalue)->findChild<QLineEdit *>();
        double preValue = currLineEdit->text().trimmed().toDouble();
        double currValue = unitConversion(preValue, currentUnitData, newUnitData);
        currLineEdit->setText(QString::number(currValue));
    }
    //update unit item user data
    comboDatas[row] = newUnitData;
}


void designTab::slot_saveAllButton(bool isChecked){
    bool isOK = true;
    QJsonObject newObj = saveInJsonObj();
    QJsonObject freObj = parseJson::getSubJsonObj(newObj, "FreSetting");
    QJsonObject farObj = parseJson::getSubJsonObj(newObj, "ThetaPhiStep");
    QJsonObject varObj = parseJson::getSubJsonObj(newObj, "varsValue");
    if(freObj.isEmpty() || farObj.isEmpty() || varObj.isEmpty())
        isOK = false;
    else{
        obj.insert("FreSetting", freObj);
        obj.insert("ThetaPhiStep", farObj);
        obj.insert("varsValue", varObj);
        QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentDesignPath"]).arg(global::getInfoFromRel("Problem"));
        if(!parseJson::write(jsonPath, obj))
            isOK = false;
    }
    if(isOK)
        this->close();
    else
        QMessageBox::critical(0, QString("Error"), QString("designTab.cpp:416: error: Cannot update in json file"));
}
