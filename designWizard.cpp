#include "designWizard.h"

designWizard::designWizard(const QString &path, QWidget *parent) : QWizard(parent){
    this->jsonPath = path;
    qDebug() << "treeModel:jsonFile=" << path;
    this->obj = parseJson::getJsonObj(jsonPath);
    //setButtonText(QWizard::BackButton, "<上一步");
    //setButtonText(QWizard::NextButton, "下一步>");
    if(obj.isEmpty()){
        QMessageBox::critical(this, tr("Error"), tr("Cannot parse jsonFile %1").arg(jsonPath));
    }
    else{
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
}
