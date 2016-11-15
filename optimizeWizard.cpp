#include "optimizeWizard.h"

optimizeWizard::optimizeWizard(QJsonObject &obj, QWidget *parent) : QWizard(parent){
    this->obj = obj;
    //remove help menu
    this->setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    //this->setWizardStyle(QWizard::ModernStyle);
    this->setWindowTitle("优化向导");
    this->setOption(QWizard::NoBackButtonOnStartPage);
    //this->setOption(QWizard::NoCancelButton);
    this->setButtonText(QWizard::NextButton, "下一步>");
    this->setButtonText(QWizard::CancelButton, "取消");
    this->setButtonText(QWizard::FinishButton, "完成");
    this->setMinimumSize(880, 580);

    this->optimizePreFar = new wizardDesignPerformance(this->obj, this);
    addPage(optimizePreFar);
    this->optimizeAXL = new wizardOptimizeAXL(this->obj, this);
    addPage(optimizeAXL);
    this->optimizeVariables = new wizardOptimizeVariables(this->obj, this);
    addPage(optimizeVariables);
    this->optimizeAlg = new wizardOptimizeAlg(this);
    addPage(optimizeAlg);
}

bool optimizeWizard::validateCurrentPage(){
    return true;
}

bool optimizeWizard::update2JsonFile(){
    QJsonObject prefarObj = optimizePreFar->saveInJsonObj();
    QJsonObject axlObj = optimizeAXL->saveInJsonObj();
    QJsonObject varsObj = optimizeVariables->saveInJsonObj();

    QJsonObject freObj = parseJson::getSubJsonObj(prefarObj, "FreSetting");
    QJsonObject farObj = parseJson::getSubJsonObj(prefarObj, "ThetaPhiStep");
    QJsonObject gainObj = parseJson::getSubJsonObj(axlObj, "GainSetting");
    QJsonObject axialObj = parseJson::getSubJsonObj(axlObj, "AxialratioSetting");
    QJsonObject lossObj = parseJson::getSubJsonObj(axlObj, "VSWRSetting");
    QJsonObject varObj = parseJson::getSubJsonObj(varsObj, "variables");

    if(freObj.isEmpty() || farObj.isEmpty() || gainObj.isEmpty() || axialObj.isEmpty()
                || lossObj.isEmpty() || varObj.isEmpty())
        return false;
    obj.insert("FreSetting", freObj);
    obj.insert("ThetaPhiStep", farObj);
    obj.insert("GainSetting", gainObj);
    obj.insert("AxialratioSetting", axialObj);
    obj.insert("VSWRSetting", lossObj);
    obj.insert("variables", varObj);
    QString jsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentOptimizePath"]).arg(global::getInfoFromRel("Problem"));
    bool isWritenInJson = parseJson::write(jsonPath, obj);
    return isWritenInJson;
}
