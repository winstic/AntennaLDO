#ifndef WIZARDDESIGNVARIABLES_H
#define WIZARDDESIGNVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
#include <QVector>
#include "../Global/global.h"
#include "../Global/macrodefined.h"
#include "../Utility/sqliteManage.h"
#include "../Utility/parsejson.h"

class wizardDesignVariables : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignVariables(QJsonObject &obj, QWidget *parent = 0);
    ~wizardDesignVariables(){}
    QJsonObject saveInJsonObj();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    bool validatePage();

public slots:
    void slot_LinetextChange(QString text);
    void slot_sliderValueChange(QString);
    void slot_unitchange(QString);

private:
    void initUnitComBo(QComboBox* comb);
    bool wizardDialogWithTable();
    QString getSliderSheet();
    bool readDefaultVars();
    double unitConversion(double sourceData, int preunit, int curunit);
    void insert2table(const int &row, const int &clomun, const QString &itemValue);

    QJsonObject obj;
    QTableWidget *varTable;
    QMap<QString, QString> defaultVars;
    QMap<int, int> comboDatas;      //save combobox data
    QSignalMapper *signalsmapSlider;  //use signalmaper manage signals in table
    QSignalMapper *signalsmapUnit;  //use signalmaper manage signals in table
    //QVector<varInfo> varinfos;
    enum VARCOLUMN{varnote = 0, varvalue, varunit};
};

#endif // WIZARDDESIGNMODELPARAMETER_H
