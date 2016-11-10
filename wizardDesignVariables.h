﻿#ifndef WIZARDDESIGNVARIABLES_H
#define WIZARDDESIGNVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
#include <QVector>
#include "macrodefined.h"
#include "sqliteManage.h"
#include "parsejson.h"
#include "global.h"

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
    void slot_sliderValueChange(int value);
    void slot_unitchange(QString);

private:
    void initUnitComBo(QComboBox* comb);
    bool wizardDialog();
    QString getSliderSheet();
    bool readDefaultVars();
    double unitConversion(double sourceData, int preunit, int curunit);

    QJsonObject obj;
    QMap<QString, QString> defaultVars;
    QMap<int, int> comboDatas;      //save combobox data
    QSignalMapper *signalsmap;  //use signalmaper manage signals in table
    QVector<varInfo> varinfos;
};

#endif // WIZARDDESIGNMODELPARAMETER_H
