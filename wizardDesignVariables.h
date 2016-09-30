#ifndef WIZARDDESIGNVARIABLES_H
#define WIZARDDESIGNVARIABLES_H

#include <QWizardPage>
#include "global.h"

class wizardDesignVariables : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignVariables(QJsonObject obj, QWidget *parent = 0);
    ~wizardDesignVariables(){}

private:
    QJsonObject obj;

    void wizardDialog();
    void initLayout();
};

#endif // WIZARDDESIGNMODELPARAMETER_H
