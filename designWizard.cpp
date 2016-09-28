#include "designWizard.h"

designWizard::designWizard(const QString &path, QWidget *parent) : QWizard(parent){
    this->jsonPath = path;
    this->obj = QJsonObject();
    if(readJsonFile()){
        this->designPerformance = new wizardDesignPerformance(this->obj, this);
        setWindowTitle("设计向导");
        setButtonText(QWizard::NextButton, "下一步>");

        addPage(designPerformance);
    }
}

bool designWizard::readJsonFile(){
    QFile file(jsonPath);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, tr("Error"), tr("Cannot read file %1").arg(jsonPath));
        return false;
    }
    else{
        QByteArray byteArray = file.readAll();
        file.close();
        QJsonParseError jsonError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray, &jsonError);
        if(jsonError.error == QJsonParseError::NoError){
            if(jsonDocument.isObject()){
                obj = jsonDocument.object();
            }
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
