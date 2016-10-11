#include "wizardDesignVariables.h"
#include "global.h"

wizardDesignVariables::wizardDesignVariables(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    readDefaultVars();
    wizardDialog();
}

void wizardDesignVariables::readDefaultVars(){
    QJsonObject defaultVarsObj = parseJson::getSubJsonObj(obj, "varsValue");
    if(defaultVarsObj.isEmpty()){
        QMessageBox::critical(0, tr("Error"), tr("Cannot parse 'varsValue' in json file"));
        return;
    }
    for(QJsonObject::iterator iter = defaultVarsObj.begin(); iter != defaultVarsObj.end(); ++ iter){
        defaultVars[iter.key()] = iter.value().toString().trimmed();
    }
}

void wizardDesignVariables::wizardDialog(){
    setTitle(tr("模型设置"));
    setSubTitle(tr("模型设置"));
    QJsonObject variablesObj = parseJson::getSubJsonObj(obj, "variables");
    if(variablesObj.isEmpty()){
        QMessageBox::critical(this, tr("Error"), tr("Cannot parse 'variables' in json file"));
        return;
    }
    QJsonObject varObj;
    QString varKey;
    QStringList varValue;
    int posx = 0, valueListLength;
    double realValue;
    QGridLayout *gridLayout = new QGridLayout;
    QRegExp rx("^(-?\d+)(\.\d+)?$");
    QRegExpValidator *floatValid = new QRegExpValidator(rx);      //float

    for(QJsonObject::iterator iter = variablesObj.begin(); iter != variablesObj.end(); ++ iter){
        // iter format: "W1":{"note" : "介质板宽度W1(m)", "W1" : "0.025"}
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
            varInfo tempVarInfo;
            tempVarInfo.lower = startValue;
            tempVarInfo.upper = stopValue;
            tempVarInfo.varKey = varKey;
            tempVarInfo.varSlider = varSlider;
            tempVarInfo.varEdit = valueEdit;
            varinfos.append(tempVarInfo);
            connect(varSlider, SIGNAL(valueChanged(int)), this, SLOT(slot_sliderValueChange(int)));

        }
        connect(valueEdit, SIGNAL(textChanged(QString)), this, SLOT(slot_LinetextChange(QString)));
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

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacerItem(new QSpacerItem(3, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addLayout(hLayout);
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(layout);
}

QComboBox* wizardDesignVariables::initUnitComBo(){
    QComboBox *comb = new QComboBox;
    comb->addItem("mm");
    comb->addItem("cm");
    comb->addItem("λ");
    comb->addItem("m");
    comb->addItem("km");
    comb->setCurrentIndex(3);
    return comb;
}

QString wizardDesignVariables::getSliderSheet(){
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

QJsonObject wizardDesignVariables::saveInJsonObj(){

}

bool wizardDesignVariables::validateCurrentPage(){
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

