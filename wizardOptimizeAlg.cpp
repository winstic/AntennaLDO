#include "wizardOptimizeAlg.h"

wizardOptimizeAlg::wizardOptimizeAlg(QJsonObject &obj, QWidget *parent) : QWizardPage(parent){
    this->obj = obj;
    setTitle(tr("优化算法设置"));
    setSubTitle(tr("设置算法参数"));
}

bool wizardOptimizeAlg::validatePage(){
    return true;
}
