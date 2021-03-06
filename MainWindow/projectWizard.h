﻿#ifndef PROJECTWIZARD_H
#define PROJECTWIZARD_H

#include <QLineEdit>
#include <QWizard>
#include <QWizardPage>
#include <QDir>
#include <QFile>
#include "../Utility/sqliteManage.h"
#include "wizardIntroduce.h"
#include "wizardAddSetting.h"
#include "wizardSelectPy.h"
//#include "config.h"

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
    //config* confManage;
    QString atnName;
    QString projectName;
    QString projectPath;
    QString projectFullPath;

	void createProject();
};

#endif
