#ifndef WIZARDOPTIMIZEALG_H
#define WIZARDOPTIMIZEALG_H

#include <QtWidgets>
#include <QWizardPage>
#include "parsejson.h"

class wizardOptimizeAlg : public QWizardPage{
    Q_OBJECT

public:
    wizardOptimizeAlg(QJsonObject &obj, QWidget *parent = 0);
    ~wizardOptimizeAlg(){}

protected:
    bool validatePage();

private:
    QJsonObject obj;
};

#endif // WIZARDOPTIMIZEALG_H
