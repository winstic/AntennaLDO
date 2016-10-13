#ifndef WIZARDDESIGNVARIABLES_H
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
    bool validateCurrentPage();

public slots:
    void slot_LinetextChange(QString text);
    void slot_sliderValueChange(int value);
private:
    QComboBox* initUnitComBo();
    bool wizardDialog();
    QString getSliderSheet();
    bool readDefaultVars();

    QJsonObject obj;
    QMap<QString, QString> defaultVars;
    QVector<varInfo> varinfos;
};

#endif // WIZARDDESIGNMODELPARAMETER_H
