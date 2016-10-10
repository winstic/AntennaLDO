#ifndef WIZARDDESIGNVARIABLES_H
#define WIZARDDESIGNVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
#include "macrodefined.h"
#include "sqliteManage.h"
#include "parsejson.h"

class wizardDesignVariables : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignVariables(QJsonObject &obj, QWidget *parent = 0);
    ~wizardDesignVariables(){}

private:
    QComboBox* initUnitComBo();
    void wizardDialog();
    void initLayout();
    QString getSliderSheet();
    void readDefaultVars();

    QJsonObject obj;
    QMap<QString, QString> defaultVars;
};

#endif // WIZARDDESIGNMODELPARAMETER_H
