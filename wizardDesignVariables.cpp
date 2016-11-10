#include "wizardDesignVariables.h"
#include "global.h"

wizardDesignVariables::wizardDesignVariables(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    this->signalsmap = new QSignalMapper;
    readDefaultVars();
    wizardDialog();
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

bool wizardDesignVariables::wizardDialog(){
    setTitle(tr("模型设置"));
    setSubTitle(tr("模型设置"));
    QJsonObject variablesObj = parseJson::getSubJsonObj(obj, "variables");
    if(variablesObj.isEmpty()){
        QMessageBox::critical(0, QString("Error"), QString("wizardDesignVariables.cpp:27: error: Cannot parse 'variables' in json file"));
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
        //valueEdit->setFixedWidth(240);
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
            if(stopValue == startValue){
                varSlider->setValue(100);
                varSlider->setEnabled(false);
            }
            else{
                int sliderValue = 100 * (realValue - startValue) / (stopValue - startValue);
                varSlider->setValue(sliderValue);
            }
            //realValue =startValue + (varSlider->value()*1.0 / 100) *(stopValue - startValue);
            //!conversion slider value and edit value
            //!
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

            connect(varSlider, SIGNAL(valueChanged(int)), this, SLOT(slot_sliderValueChange(int)));

        }
        tempVarInfo.varKey = varKey;
        tempVarInfo.varEdit = valueEdit;
        varinfos.append(tempVarInfo);
        connect(valueEdit, SIGNAL(textChanged(QString)), this, SLOT(slot_LinetextChange(QString)));
        //valueEdit->installEventFilter(this);        //install filter in this dialog(在对话框上为QLineEdit安装过滤器)
        //connect(valueEdit, SIGNAL(), this, SLOT(slot_LinetextChange(QString)));
        QComboBox *unitComBo = new QComboBox;
        initUnitComBo(unitComBo);
        //unitComBo->setFixedWidth(50);
        gridLayout->addWidget(unitComBo, posx, 2);
        //map combobox signal
        //connect(unitComBo, SIGNAL(currentIndexChanged(int)), signalsmap, SLOT(map()));
        //signalsmap->setMapping(unitComBo, QString("%1").arg(posx));
        //in 'posx'th row, save default unitComBo current data
        comboDatas.insert(posx, unitComBo->currentData(ROLE_MARK_UNIT).toInt());

        ++ posx;
    }
    //connect(signalsmap, SIGNAL(mapped(QString)), this, SLOT(slot_unitchange(QString)));

    gridLayout->setAlignment(Qt::AlignHCenter);
    gridLayout->setAlignment(Qt::AlignVCenter);
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(2,20,2,2);

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
    hLayout->addLayout(gridLayout, 1);
    hLayout->addWidget(atnPhoto, 1);

    QVBoxLayout *vlayout = new QVBoxLayout;
    //vlayout->addSpacerItem(new QSpacerItem(3, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vlayout->addLayout(hLayout);
    //vlayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addLayout(vlayout);
    setLayout(layout);
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
    foreach(varInfo var, varinfos){
        varObj.insert(var.varKey, var.varEdit->text().trimmed());
    }
    saveObj.insert("varsValue", varObj);
    return saveObj;
}

bool wizardDesignVariables::validatePage(){
    return true;
}

//rewrite event filter function
bool wizardDesignVariables::eventFilter(QObject *watched, QEvent *event){
    foreach(varInfo var, varinfos){
        if(watched == var.varEdit){
            if(event->type() == QEvent::MouseButtonDblClick){
                var.varEdit->setReadOnly(false);
            }
        }
    }
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

void wizardDesignVariables::slot_sliderValueChange(int value){
    QSlider* selectSlider = static_cast<QSlider* >(sender());
    foreach(varInfo var, varinfos){
        if(var.varSlider == selectSlider){
            //qDebug() << var.varKey << "---" << var.varEdit;
            double realValue = (var.upper - var.lower)/100.0 * value + var.lower;
            //var.varEdit->setReadOnly(true);
            var.varEdit->setText(QString::number(realValue));
        }
    }
    //selectEdit->setText(QString::number(value));
    //qDebug() << selectEdit->text();
}

void wizardDesignVariables::slot_unitchange(QString pos){
    Q_ASSERT(!comboDatas.isEmpty());
    int row = pos.toInt();
    int currentUnitData = comboDatas[row];
    QComboBox *selectCombox = static_cast<QComboBox* >(sender());
    qDebug() << selectCombox->currentText();
    int newUnitData = selectCombox->currentData(ROLE_MARK_UNIT).toInt();
    qDebug() << currentUnitData << newUnitData;
    if(currentUnitData != MARK_UNIT_LAMBDA && newUnitData != MARK_UNIT_LAMBDA &&
            newUnitData != currentUnitData){
        /*double preValueMin = varTable->item(row, varmin)->text().trimmed().toDouble();
        double preValueMax = varTable->item(row, varmax)->text().trimmed().toDouble();
        double currentValueMin = unitConversion(preValueMin, currentUnitData, newUnitData);
        double currentValueMax = unitConversion(preValueMax, currentUnitData, newUnitData);
        qDebug() << currentValueMin << currentValueMax;
        insert2table(row, varmin, QString::number(currentValueMin));
        insert2table(row, varmax, QString::number(currentValueMax));*/
    }
    comboDatas[row] = newUnitData;
}


