#ifndef OPTIMIZEWIZARD_H
#define OPTIMIZEWIZARD_H

#include <QWizard>
#include <QWizardPage>
#include <QFile>
#include <QTextStream>
#include "../Global/global.h"
#include "../Global/macrodefined.h"
#include "../Utility/parsejson.h"
#include "../Design/wizardDesignPerformance.h"
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

    void madeOptimalFile();
};

#endif // OPTIMIZEWIZARD_H
