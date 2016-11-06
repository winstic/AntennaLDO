#ifndef WIZARDOPTIMIZEGAINAXIALLOSS_H
#define WIZARDOPTIMIZEGAINAXIALLOSS_H

#include <QtWidgets>
#include <QWizardPage>
#include "parsejson.h"
#include "global.h"

class wizardOptimizeAXL : public QWizardPage{
    Q_OBJECT

public:
    wizardOptimizeAXL(QJsonObject &obj, QWidget *parent = 0);
    ~wizardOptimizeAXL(){}
    QJsonObject saveInJsonObj();

protected:
    bool validatePage();

public slots:
    void slot_cellClick(int, int);
    void slot_changeOptimaltype(int);
    void slot_changeLosstype(int);

private:
    bool gainSetting();
    bool axialSetting();
    bool lossSetting();
    void initLayout();
    void initOptimalTypeComBox(QComboBox *combox);
    void initLossTypeComBox(QComboBox *combox);
    void insert2table(QTableWidget *table, const int &row, const int &clomun, const QString &itemValue);

    QJsonObject obj;
    QTableWidget* gainTable;
    QTableWidget* axialTable;
    QTableWidget* lossTable;
    QGroupBox *groupBoxGain;
    QGroupBox *groupBoxAxial;
    QGroupBox *groupBoxLoss;
    enum GACOLUMN{cthetalower = 0, cthetaupper, cphilower, cphiupper, coptimaltype, cdelta, cobjvalue, cweight};
    enum LOSSCOLUMN{cz0real = 0, cz0imag, closstype, clossoptimaltype, cdeltareal, cdeltaimag, cobjreal, cobjimag, clossweight};
};

#endif // WIZARDOPTIMIZEGAINAXIALLOSS_H
