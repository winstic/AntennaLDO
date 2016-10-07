#include "wizardDesignVariables.h"

wizardDesignVariables::wizardDesignVariables(QJsonObject obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    wizardDialog();
}

void wizardDesignVariables::wizardDialog(){
    setTitle("模型设置");
    if(!this->obj.contains("variables")){
        QMessageBox::critical(this, tr("Error"), tr("not exist key('variables') in json file"));
        return;
    }
    QJsonValue variablesValue = this->obj.value("variables");
    if(!variablesValue.isObject()){
        QMessageBox::critical(this, tr("Error"), tr("Json data format error"));
        return;
    }
    QJsonObject variablesObj, varObj;
    variablesObj = variablesValue.toObject();

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
        varValue = singleListRegularStr(varObj.value(varKey).toString().trimmed());
        valueListLength = varValue.length();
        if(valueListLength == 1){
            QLineEdit *valueEdit = new QLineEdit(varValue[0]);
            valueEdit->setFixedWidth(240);
            valueEdit->setEnabled(false);
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
            varSlider->setValue(50);
            varSlider->setSingleStep(1);
            realValue = (varSlider->value()*1.0 / 100) *
                    (QString(varValue[1]).trimmed().toDouble() - QString(varValue[0]).trimmed().toDouble());
            varEdit->setText(QString::number(realValue));
            varEdit->setEnabled(false);
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
    setLayout(gridLayout);
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
