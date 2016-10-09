#include "designWizard.h"

designWizard::designWizard(const QString &path, QWidget *parent) : QWizard(parent){
    this->jsonPath = path;
    qDebug() << "treeModel:jsonFile=" << path;
    this->obj = QJsonObject();
    //setButtonText(QWizard::BackButton, "<上一步");
    //setButtonText(QWizard::NextButton, "下一步>");
    if(readJsonFile()){
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

bool designWizard::readJsonFile(){
    QFile file(jsonPath);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, tr("Error"), tr("Cannot read file %1").arg(jsonPath));
        return false;
    }

    QByteArray byteArray = file.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray, &jsonError);
    if(jsonError.error == QJsonParseError::NoError){
        if(jsonDocument.isObject()){
            obj = jsonDocument.object();
        }
    }
    return true;
}

bool designWizard::writeJsonFile(const QJsonObject &obj){
    QFile file(jsonPath);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, tr("Error"), tr("Cannot read file %1").arg(jsonPath));
        return false;
    }
    QJsonDocument jsonDocument;
    jsonDocument.setObject(obj);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    QTextStream out(&file);
    out << QString(byteArray);
    file.close();
    return true;
}
