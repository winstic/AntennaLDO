#ifndef DESIGNWIZARD_H
#define DESIGNWIZARD_H

#include <QWizard>
#include <QWizardPage>
#include <QFile>
#include <QTextStream>
#include "macrodefined.h"
#include "wizardDesignPerformance.h"
#include "wizardDesignVariables.h"
#include "parsejson.h"

class designWizard : public QWizard{
    Q_OBJECT

public:
    designWizard(const QString &path, QWidget *parent = 0);
    ~designWizard(){}
    bool validateCurrentPage();

private:

    wizardDesignPerformance *designPerformance;
    wizardDesignVariables *designVariables;
    QString jsonPath;
    QJsonObject obj;
};

#endif // DESIGNWIZARD_H
