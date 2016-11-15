#ifndef OPTIMIZEWIZARD_H
#define OPTIMIZEWIZARD_H

#include <QWizard>
#include <QWizardPage>
#include <QFile>
#include <QTextStream>
#include "macrodefined.h"
#include "parsejson.h"
#include "wizardDesignPerformance.h"
#include "wizardOptimizeGainAxialLoss.h"
#include "wizardOptimizeVariables.h"
#include "wizardOptimizeAlg.h"

class optimizeWizard : public QWizard{
    Q_OBJECT
public:
    optimizeWizard(QJsonObject &obj, QWidget *parent = 0);
    ~optimizeWizard(){}
    bool update2JsonFile();

protected:
    bool validateCurrentPage();

private:
    QJsonObject obj;
    wizardDesignPerformance *optimizePreFar;
    wizardOptimizeAXL *optimizeAXL;
    wizardOptimizeVariables *optimizeVariables;
    wizardOptimizeAlg *optimizeAlg;

};

#endif // OPTIMIZEWIZARD_H
