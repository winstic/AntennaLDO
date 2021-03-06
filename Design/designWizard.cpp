﻿#include "designWizard.h"

designWizard::designWizard(QJsonObject &obj, QWidget *parent) : QWizard(parent){
    this->obj = obj;
    this->designPerformance = new wizardDesignPerformance(this->obj, this);
    addPage(designPerformance);
    this->designVariables = new wizardDesignVariables(this->obj, this);
    addPage(designVariables);
    //remove help menu
    this->setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    //this->setWizardStyle(QWizard::ModernStyle);
    this->setWindowTitle("设计向导");
    this->setOption(QWizard::NoBackButtonOnStartPage);
    //this->setOption(QWizard::NoCancelButton);
    this->setButtonText(QWizard::NextButton, "下一步>");
    this->setButtonText(QWizard::CancelButton, "取消");
    this->setButtonText(QWizard::FinishButton, "完成");
    this->setMinimumSize(880, 580);
}

bool designWizard::validateCurrentPage(){
    //bool isUpdate = update2JsonFile();
    //qDebug() << "isUpdate: " << isUpdate;
    //return isUpdate;
    return true;
}

bool designWizard::update2JsonFile(){
    QJsonObject perObj = designPerformance->saveInJsonObj();
    QJsonObject varsObj = designVariables->saveInJsonObj();
    QJsonObject freObj = parseJson::getSubJsonObj(perObj, "FreSetting");
    QJsonObject farObj = parseJson::getSubJsonObj(perObj, "ThetaPhiStep");
    QJsonObject varObj = parseJson::getSubJsonObj(varsObj, "varsValue");
    if(freObj.isEmpty() || farObj.isEmpty() || varObj.isEmpty())
        return false;
    obj.insert("FreSetting", freObj);
    obj.insert("ThetaPhiStep", farObj);
    obj.insert("varsValue", varObj);
    QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentDesignPath"]).arg(global::getInfoFromRel("Problem"));
    bool isWriteInJson = parseJson::write(jsonPath, obj);
    return isWriteInJson;
}
