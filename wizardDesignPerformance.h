#ifndef WIZARDDESIGNPERFORMANCE_H
#define WIZARDDESIGNPERFORMANCE_H

#include <QWizardPage>
#include <QFile>
#include "global.h"

class wizardDesignPerformance : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignPerformance(QJsonObject obj, QWidget *parent = 0);
    ~wizardDesignPerformance(){}
private:
    void wizardDialog();
    void initComBoBox();
    void initLayout();

    QJsonObject obj;
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

};

#endif // WIZARDDESIGNFREQUENCY_H
