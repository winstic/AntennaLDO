﻿#ifndef WIZARDDESIGNPERFORMANCE_H
#define WIZARDDESIGNPERFORMANCE_H

#include <QtWidgets>
#include <QWizardPage>
#include <QFile>
#include "../Global/macrodefined.h"
#include "../Utility/parsejson.h"

class wizardDesignPerformance : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignPerformance(QJsonObject &obj, QWidget *parent = 0);
    ~wizardDesignPerformance(){}
    QJsonObject saveInJsonObj();

protected:
    bool validatePage();

private:
    bool frequencySetting();
    bool farFieldSetting();
    void initComBoBox();
    void initLayout();

    QJsonObject obj;
    //frequencySetting
    QLabel *freStartLabel;
    QLabel *freEndLabel;
    QLabel *freNumberLabel;
    QLabel *sweepTypeLabel;
    QLabel *PMLabel;    
    QLineEdit *freStartEdit;
    QLineEdit *freEndEdit;
    QLineEdit *freNumberEdit;
    QComboBox *sweeptypeComb;
    QComboBox *PMComb;
    QGroupBox *groupBoxFrequency;

    //farFieldSetting
    QLabel *thetaStartLabel;
    QLabel *thetaEndLabel;
    QLabel *thetaStepLabel;
    QLabel *phiStartLabel;
    QLabel *phiEndLabel;
    QLabel *phiStepLabel;
    QLineEdit *thetaStartEdit;
    QLineEdit *thetaEndEdit;
    QLineEdit *thetaStepEdit;
    QLineEdit *phiStartEdit;
    QLineEdit *phiEndEdit;
    QLineEdit *phiStepEdit;
    QGroupBox *groupBoxFarField;

    bool isValid;
};

#endif // WIZARDDESIGNFREQUENCY_H
