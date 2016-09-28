﻿#ifndef PROJECTWIZARD_H
#define PROJECTWIZARD_H

#include <QLineEdit>
#include <QWizard>
#include <QWizardPage>
#include <QDir>
#include <QFile>
#include "wizardIntroduce.h"
#include "sqliteManage.h"
#include "wizardAddSetting.h"
#include "wizardSelectPy.h"

class projectWizard :public QWizard{
    Q_OBJECT

public:
    projectWizard(QString antennaName = NULL, QWidget *parent = 0);
    ~projectWizard(){}
    QString getProjectName() const;
    bool validateCurrentPage();

private:
    wizardIntroduce* introduce;
    wizardAddSetting* addSetting;
    wizardSelectPy* selectPy;
    QString atnName;
    QString projectName;

	void createProject();
    bool copyFile(QString sourceFile, QString targetFile, bool coverFileIfExist = 1);
};

#endif
