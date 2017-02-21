#ifndef DESIGNWIZARD_H
#define DESIGNWIZARD_H

#include <QWizard>
#include <QWizardPage>
#include <QFile>
#include <QTextStream>
#include "../Global/macrodefined.h"
#include "../Utility/parsejson.h"
#include "wizardDesignPerformance.h"
#include "wizardDesignVariables.h"

class designWizard : public QWizard{
    Q_OBJECT

public:
    designWizard(QJsonObject &obj, QWidget *parent = 0);
    ~designWizard(){}
    bool update2JsonFile();

protected:
    bool validateCurrentPage();

private:
    wizardDesignPerformance *designPerformance;
    wizardDesignVariables *designVariables;
    QJsonObject obj;
};

#endif // DESIGNWIZARD_H
