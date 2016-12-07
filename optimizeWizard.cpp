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
    if(this->currentPage()->nextId() == -1){
        madeOptimalFile();
    }
    return true;
}

void optimizeWizard::madeOptimalFile(){
    QString DEA4ADglobalPath = QString("./DEA4AD/trunk");
    QString algPath = optimizeAlg->getAlgPath();
    QString algName = optimizeAlg->getAlgName();
    QString projectFullPath = sysParam["WorkingProjectPath"];
    if(! global::copyFile(QString("%1/global_conf.json").arg(DEA4ADglobalPath), QString("%1/global_conf.json").arg(projectFullPath)) ||
            ! global::copyFile(QString("%1/%2_conf.json").arg(algPath).arg(algName), QString("%1/%2_conf.json").arg(projectFullPath).arg(algName))){
        QMessageBox::critical(0, QString("Error"), QString("optimizeWizard.cpp:40: error: 算法文件创建失败！"));
        return;
    }

    sysParam["Algorithm"] = algName;
    /*if(global::getInfoFromRel("Algorithm").isNull())
        global::addedInfoInRel(QString("Algorithm"), algName);*/
}

bool optimizeWizard::update2JsonFile(){
    QJsonObject prefarObj = optimizePreFar->saveInJsonObj();
    QJsonObject axlObj = optimizeAXL->saveInJsonObj();
    QJsonObject varsObj = optimizeVariables->saveInJsonObj();
    QJsonObject gloAlgObj = optimizeAlg->saveInJsonObj();

    QJsonObject freObj = parseJson::getSubJsonObj(prefarObj, "FreSetting");
    QJsonObject farObj = parseJson::getSubJsonObj(prefarObj, "ThetaPhiStep");
    QJsonObject gainObj = parseJson::getSubJsonObj(axlObj, "GainSetting");
    QJsonObject axialObj = parseJson::getSubJsonObj(axlObj, "AxialratioSetting");
    QJsonObject lossObj = parseJson::getSubJsonObj(axlObj, "VSWRSetting");
    QJsonObject varObj = parseJson::getSubJsonObj(varsObj, "variables");
    QJsonObject globalObj = parseJson::getSubJsonObj(gloAlgObj, "global");
    QJsonObject algorithmObj = parseJson::getSubJsonObj(gloAlgObj, "algorithm");

    if(freObj.isEmpty() || farObj.isEmpty() || gainObj.isEmpty() || axialObj.isEmpty()
                || lossObj.isEmpty() || varObj.isEmpty() || globalObj.isEmpty() || algorithmObj.isEmpty())
        return false;
    obj.insert("FreSetting", freObj);
    obj.insert("ThetaPhiStep", farObj);
    obj.insert("GainSetting", gainObj);
    obj.insert("AxialratioSetting", axialObj);
    obj.insert("VSWRSetting", lossObj);
    obj.insert("variables", varObj);
    QString problemJsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentOptimizePath"]).arg(global::getInfoFromRel("Problem"));
    QString globalJsonPath = QString("%1/global_conf.json").arg(sysParam["CurrentOptimizePath"]);
    QString algorithmJsonPath = QString("%1/%2_conf.json").arg(sysParam["CurrentOptimizePath"]).arg(sysParam["Algorithm"]);

    bool isWritenInJson = (parseJson::write(problemJsonPath, obj)
                           && parseJson::write(globalJsonPath, globalObj)
                           && parseJson::write(algorithmJsonPath, algorithmObj) );
    return isWritenInJson;
}
