#include "wizardDesignVariables.h"
#include "global.h"

wizardDesignVariables::wizardDesignVariables(QJsonObject obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    readDefaultVars();
    wizardDialog();
}

void wizardDesignVariables::readDefaultVars(){
    QJsonObject defaultVarsObj = parseJson::getSubJsonObj(obj, "defaultvars");
    for(QJsonObject::iterator iter = defaultVarsObj.begin(); iter != defaultVarsObj.end(); ++ iter){
        vbsVariables[iter.key()] = iter.value().toString().trimmed();
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

    for(QJsonObject::iterator iter = variablesObj.begin(); iter != variablesObj.end(); ++ iter){
        // iter format: "W1":{"note" : "介质板宽度W1(m)", "W1" : "0.025"}
        varKey = iter.key();
        varObj = iter.value().toObject();
        QLabel *keyLabel = new QLabel(varObj.value("note").toString().trimmed());
        //keyLabel->setFixedWidth(100);
        keyLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
        gridLayout->addWidget(keyLabel, posx, 0);

        // init line edit and layout
        varValue = global::singleListRegularStr(varObj.value(varKey).toString().trimmed());        
        valueListLength = varValue.length();
        if(valueListLength == 1){
            QLineEdit *valueEdit = new QLineEdit(varValue[0]);
            valueEdit->setFixedWidth(240);
            valueEdit->setReadOnly(true);
            gridLayout->addWidget(valueEdit, posx, 1);
            //delete valueEdit;
        }
        else{
            QVBoxLayout *vLayout = new QVBoxLayout;
            QLineEdit *varEdit = new QLineEdit;
            QSlider *varSlider = new QSlider(Qt::Horizontal);

            varSlider->setStyleSheet(getSliderSheet());
            varSlider->setMinimum(0);
            varSlider->setMaximum(100);            
            varSlider->setSingleStep(1);

            double stopValue = QString(varValue[1]).trimmed().toDouble();
            double startValue = QString(varValue[0]).trimmed().toDouble();
            realValue = vbsVariables[varKey].trimmed().toDouble();
            int sliderValue = 100 * (realValue - startValue) / (stopValue - startValue);
            //realValue =startValue + (varSlider->value()*1.0 / 100) *(stopValue - startValue);

            varSlider->setValue(sliderValue);
            varEdit->setText(QString::number(realValue));

            varEdit->setReadOnly(true);
            varEdit->setFixedWidth(240);
            vLayout->addWidget(varEdit);
            vLayout->addWidget(varSlider);
            //design inner space
            vLayout->setSpacing(0);
            // design outer space
            //vLayout->setMargin(0);
            gridLayout->addLayout(vLayout, posx, 1);
        }
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
