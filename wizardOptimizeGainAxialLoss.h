#ifndef WIZARDOPTIMIZEGAINAXIALLOSS_H
#define WIZARDOPTIMIZEGAINAXIALLOSS_H

#include <QtWidgets>
#include <QWizardPage>
#include "parsejson.h"

class wizardOptimizeAXL : public QWizardPage{
    Q_OBJECT

public:
    wizardOptimizeAXL(QJsonObject &obj, QWidget *parent = 0);
    ~wizardOptimizeAXL(){}

protected:
    bool validatePage();

private:
    bool gainSetting();
    bool axialSetting();
    bool lossSetting();
    void initLayout();

    QJsonObject obj;
    QTableWidget* gainTable;
    QTableWidget* axialTable;
    QTableWidget* lossTable;
    QGroupBox *groupBoxGain;
    QGroupBox *groupBoxAxial;
    QGroupBox *groupBoxLoss;
};

#endif // WIZARDOPTIMIZEGAINAXIALLOSS_H
