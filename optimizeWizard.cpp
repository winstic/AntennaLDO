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
