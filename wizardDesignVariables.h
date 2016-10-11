#ifndef WIZARDDESIGNVARIABLES_H
#define WIZARDDESIGNVARIABLES_H

#include <QtWidgets>
#include <QWizardPage>
#include <QVector>
#include "macrodefined.h"
#include "sqliteManage.h"
#include "parsejson.h"

typedef struct{
    double lower;
    double upper;
    QString varKey;
    QSlider *varSlider;
    QLineEdit *varEdit;
}varInfo;

class wizardDesignVariables : public QWizardPage{
    Q_OBJECT

public:
    wizardDesignVariables(QJsonObject &obj, QWidget *parent = 0);
    ~wizardDesignVariables(){}
    QJsonObject saveInJsonObj();

protected:
    bool validateCurrentPage();
    bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void slot_LinetextChange(QString text);
    void slot_sliderValueChange(int value);
private:
    QComboBox* initUnitComBo();
    void wizardDialog();
    void initLayout();
    QString getSliderSheet();
    void readDefaultVars();

    QJsonObject obj;
    QMap<QString, QString> defaultVars;
    QVector<varInfo> varinfos;
};

#endif // WIZARDDESIGNMODELPARAMETER_H
