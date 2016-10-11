#ifndef WIZARDDESIGNPERFORMANCE_H
#define WIZARDDESIGNPERFORMANCE_H

#include <QtWidgets>
#include <QWizardPage>
#include <QFile>
#include "macrodefined.h"
#include "parsejson.h"

class wizardDesignPerformance : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignPerformance(QJsonObject &obj, QWidget *parent = 0);
    ~wizardDesignPerformance(){}
    bool validateCurrentPage();
    QJsonObject saveInJsonObj();

private:
    void frequencySetting();
    void farFieldSetting();
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
};

#endif // WIZARDDESIGNFREQUENCY_H
