#include "wizardOptimizeVariables.h"

wizardOptimizeVariables::wizardOptimizeVariables(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    this->varTable = new QTableWidget();
    this->signalsmap = new QSignalMapper;
    setTitle(tr("优化变量设置"));
    setSubTitle(tr("设置需要优化的变量参数"));
    varTable->setColumnCount(4);
    QStringList header;
    header << "变量" << "最小值" << "最大值" << "单位";
    varTable->setHorizontalHeaderLabels(header);
    //varTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    varTable->horizontalHeader()->setSectionResizeMode(varnote, QHeaderView::Stretch);
    varTable->horizontalHeader()->setSectionResizeMode(varunit, QHeaderView::ResizeToContents);
    wizardDialog();
}

bool wizardOptimizeVariables::wizardDialog(){
    QJsonObject variablesObj = parseJson::getSubJsonObj(obj, "variables");
    if(variablesObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardOptimizeVariables.cpp:13: error: Cannot parse 'variables' in json file"));
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
        insert2table(rownumber, varnote, keyNote);
        //setting first column can not edit
        varTable->item(rownumber, varnote)->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        varTable->item(rownumber, varnote)->setWhatsThis(varKey);

        varValue = global::str2list(varObj.value(varKey).toString().trimmed());
        valueListLength = varValue.length();
        insert2table(rownumber, varmin, varValue[0]);
        if(valueListLength == 1)
            insert2table(rownumber, varmax, varValue[0]);
        else
            insert2table(rownumber, varmax, varValue[1]);
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
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(varTable, 1);
    hLayout->addWidget(atnPhoto, 1);
    setLayout(hLayout);
    return true;
}

void wizardOptimizeVariables::initUnitComBo(QComboBox *comb){
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

QJsonObject wizardOptimizeVariables::saveInJsonObj(){
    QJsonObject saveObj, varObj;
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
    saveObj.insert("variables", varObj);
    return saveObj;
}

void wizardOptimizeVariables::insert2table(const int &row, const int &clomun, const QString &itemValue){
    QTableWidgetItem *tableItem = new QTableWidgetItem(itemValue);
    tableItem->setTextAlignment(Qt::AlignCenter);
    varTable->setItem(row, clomun, tableItem);
}

double wizardOptimizeVariables::unitConversion(double sourceData, int preunit, int curunit){
    //assert(preunit != unitlambda && curunit != unitlambda);
    return sourceData * qPow(10, preunit - curunit);
}

bool wizardOptimizeVariables::validatePage(){
    return true;
}

//slots function
void wizardOptimizeVariables::slot_unitchange(QString pos){
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
        insert2table(row, varmin, QString::number(currentValueMin));
        insert2table(row, varmax, QString::number(currentValueMax));
    }
    comboDatas[row] = newUnitData;
}
