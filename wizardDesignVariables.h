#ifndef WIZARDDESIGNVARIABLES_H
#define WIZARDDESIGNVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
#include "macrodefined.h"
#include "sqliteManage.h"

class wizardDesignVariables : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignVariables(QJsonObject obj, QWidget *parent = 0);
    ~wizardDesignVariables(){}

private:
    QComboBox* initUnitComBo();
    void wizardDialog();
    void initLayout();
    QString getSliderSheet();

    QJsonObject obj;
};

#endif // WIZARDDESIGNMODELPARAMETER_H
