#ifndef WIZARDOPTIMIZEVARIABLES_H
#define WIZARDOPTIMIZEVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
#include <QMap>
#include "macrodefined.h"
#include "sqliteManage.h"
#include "parsejson.h"
#include "global.h"

class wizardOptimizeVariables : public QWizardPage{
    Q_OBJECT

public:
    wizardOptimizeVariables(QJsonObject &obj, QWidget *parent = 0);
    ~wizardOptimizeVariables(){}
    QJsonObject saveInJsonObj();

protected:
    bool wizardDialog();
    void initUnitComBo(QComboBox *comb);
    void insert2table(const int &row, const int &clomun, const QString &itemValue);
    bool validatePage();

public slots:
    void slot_unitchange(QString);

private:
    double unitConversion(double sourceData, int preunit, int curunit);

    QJsonObject obj;
    QTableWidget *varTable;
    QMap<int, int> comboDatas;
    QSignalMapper *signalsmap;  //use signalmaper manage signals in table
    enum VARCOLUMN{varnote = 0, varmin, varmax, varunit};
    //enum UNITVALUE{unitlambda = 0, unitmm, unitcm, unitm = 4, unitkm = 7};
};

#endif // WIZARDOPTIMIZEVARIABLES_H
