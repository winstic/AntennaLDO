#include "wizardDesignVariables.h"
#include "global.h"

wizardDesignVariables::wizardDesignVariables(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    this->varTable = new QTableWidget();
    this->signalsmapSlider = new QSignalMapper();
    this->signalsmapUnit = new QSignalMapper();
    setTitle(tr("模型设置"));
    setSubTitle(tr("模型设置"));
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

    readDefaultVars();
    wizardDialogWithTable();
}

bool wizardDesignVariables::readDefaultVars(){
    QJsonObject defaultVarsObj = parseJson::getSubJsonObj(obj, "varsValue");
    if(defaultVarsObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardDesignVariables.cpp:13: error: Cannot parse 'varsValue' in json file"));
        return false;
    }
    for(QJsonObject::iterator iter = defaultVarsObj.begin(); iter != defaultVarsObj.end(); ++ iter){
        defaultVars[iter.key()] = iter.value().toString().trimmed();
    }
    return true;
}

bool wizardDesignVariables::wizardDialogWithTable(){
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
        connect(valueEdit, SIGNAL(textChanged(QString)), this, SLOT(slot_LinetextChange(QString)));
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

    setLayout(hLayout);
    return true;
}

void wizardDesignVariables::initUnitComBo(QComboBox *comb){
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

QString wizardDesignVariables::getSliderSheet(){
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

QJsonObject wizardDesignVariables::saveInJsonObj(){
    QJsonObject saveObj, varObj;
    QString varKey, varValue;
    for(int i = 0; i < varTable->rowCount(); i++){
        varKey = varTable->item(i, varnote)->whatsThis().trimmed();
        varValue = varTable->cellWidget(i, varvalue)->findChild<QLineEdit *>()->text().trimmed();
        varObj.insert(varKey, varValue);
    }
    saveObj.insert("varsValue", varObj);
    return saveObj;
}

void wizardDesignVariables::insert2table(const int &row, const int &clomun, const QString &itemValue){
    QTableWidgetItem *tableItem = new QTableWidgetItem(itemValue);
    tableItem->setTextAlignment(Qt::AlignCenter);
    varTable->setItem(row, clomun, tableItem);
}

bool wizardDesignVariables::validatePage(){
    return true;
}

//rewrite event filter function
bool wizardDesignVariables::eventFilter(QObject *watched, QEvent *event){
    /*foreach(varInfo var, varinfos){
        if(watched == var.varEdit){
            if(event->type() == QEvent::MouseButtonDblClick){
                var.varEdit->setReadOnly(false);
            }
        }
    }*/
    return QWizardPage::eventFilter(watched, event);
}

double wizardDesignVariables::unitConversion(double sourceData, int preunit, int curunit){
    //assert(preunit != unitlambda && curunit != unitlambda);
    return sourceData * qPow(10, preunit - curunit);
}

//slots function
void wizardDesignVariables::slot_LinetextChange(QString text){
    //qDebug() << text;
}

void wizardDesignVariables::slot_sliderValueChange(QString sparameter){
    QStringList parameterList = sparameter.split("#");
    QSlider* selectSlider ;
    QLineEdit* selectLineEdit;
    int rowNumber, svalue, currUnitData;
    double upper, lower, newLineEditValue;
    rowNumber = parameterList.at(0).toInt();        //table rowth
    upper = parameterList.at(1).toDouble();
    lower = parameterList.at(2).toDouble();
    //get widget
    selectSlider = varTable->cellWidget(rowNumber, varvalue)->findChild<QSlider *>();
    selectLineEdit = varTable->cellWidget(rowNumber, varvalue)->findChild<QLineEdit *>();
    svalue = selectSlider->value();
    //get new edit value by slider value
    newLineEditValue = (upper - lower)/100.0 * svalue + lower;
    currUnitData = comboDatas[rowNumber];
    if(MARK_UNIT_M != currUnitData && MARK_UNIT_LAMBDA != currUnitData)
        newLineEditValue = unitConversion(newLineEditValue, MARK_UNIT_M, currUnitData);
    selectLineEdit->setText(QString::number(newLineEditValue));
}

void wizardDesignVariables::slot_unitchange(QString pos){
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


