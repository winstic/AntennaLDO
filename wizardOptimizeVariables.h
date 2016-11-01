#ifndef WIZARDOPTIMIZEVARIABLES_H
#define WIZARDOPTIMIZEVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
#include "parsejson.h"

class wizardOptimizeVariables : public QWizardPage{
    Q_OBJECT

public:
    wizardOptimizeVariables(QJsonObject &obj, QWidget *parent = 0);
    ~wizardOptimizeVariables(){}

protected:
    bool validatePage();

private:
    QJsonObject obj;
};

#endif // WIZARDOPTIMIZEVARIABLES_H
