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
    void slot_gainChangeOptimaltype(QString);
    void slot_axialChangeOptimaltype(QString);
    void slot_lossChangeType(QString pos);

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
    QSignalMapper *gainsignalsmap;  //use signalmaper manage signals in table
    QSignalMapper *axialsignalsmap;
    QSignalMapper *losssignalsmap;
    enum GACOLUMN{cthetalower = 0, cthetaupper, cphilower, cphiupper, coptimaltype, cdelta, cobjvalue, cweight};
    enum LOSSCOLUMN{cz0real = 0, cz0imag, closstype, clossoptimaltype, cdeltareal, cdeltaimag, cobjreal, cobjimag, clossweight};
};

#endif // WIZARDOPTIMIZEGAINAXIALLOSS_H
