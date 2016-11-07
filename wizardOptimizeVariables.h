#ifndef WIZARDOPTIMIZEVARIABLES_H
#define WIZARDOPTIMIZEVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
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

    QJsonObject obj;
    QTableWidget *varTable;
    QString currentUnit;
    QSignalMapper *signalsmap;  //use signalmaper manage signals in table
    enum VARCOLUMN{varnote = 0, varmin, varmax, varunit};
    //enum UNITVALUE{mm = 0, cm, m, km, lambda};
};

#endif // WIZARDOPTIMIZEVARIABLES_H
