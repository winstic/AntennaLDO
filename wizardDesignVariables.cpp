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
    QGridLayout *gridLayout = new QGridLayout;

    for(QJsonObject::iterator iter = variablesObj.begin(); iter != variablesObj.end(); ++ iter){
        // iter format: "W1":{"note" : "介质板宽度W1(m)", "W1" : "0.025"}
        varKey = iter.key();
        varObj = iter.value().toObject();
        QLabel *keyLabel = new QLabel(varObj.value("note").toString().trimmed());
        keyLabel->setAlignment(Qt::AlignRight);
        gridLayout->addWidget(keyLabel, posx, 0);

        // init line edit and layout
        varValue = singleListRegularStr(varObj.value(varKey).toString().trimmed());
        valueListLength = varValue.length();
        for(int i = 0; i < valueListLength; ++i){
            QLineEdit *valueEdit = new QLineEdit(varValue[i]);
            valueEdit->setFixedWidth(140);
            gridLayout->addWidget(valueEdit, posx, i+1);
        }
        ++ posx;
    }
    setLayout(gridLayout);
}
