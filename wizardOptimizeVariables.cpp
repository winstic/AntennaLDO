#include "wizardOptimizeVariables.h"

wizardOptimizeVariables::wizardOptimizeVariables(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    setTitle(tr("优化变量设置"));
    setSubTitle(tr("设置需要优化的变量参数"));
}

bool wizardOptimizeVariables::validatePage(){
    return true;
}
