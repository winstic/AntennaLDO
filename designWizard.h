#ifndef DESIGNWIZARD_H
#define DESIGNWIZARD_H

#include <QWizard>
#include <QWizardPage>
#include <QFile>
#include <QTextStream>
#include "global.h"
#include "wizardDesignPerformance.h"
#include "wizardDesignVariables.h"

class designWizard : public QWizard{
    Q_OBJECT

public:
    designWizard(const QString &path, QWidget *parent = 0);
    ~designWizard(){}
    inline QJsonObject getJsonObj() const{return obj;}

private:
    bool readJsonFile();
    bool writeJsonFile(const QJsonObject &obj);

    wizardDesignPerformance *designPerformance;
    wizardDesignVariables *designVariables;
    QMap<QString, QString> modeVariables;
    QMap<QString, QString> freVariables;
    QString jsonPath;
    QJsonObject obj;
};

#endif // DESIGNWIZARD_H
