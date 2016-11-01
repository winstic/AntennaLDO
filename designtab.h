#ifndef DESIGNTAB_H
#define DESIGNTAB_H

#include <QtWidgets>
#include <QVector>
#include "sqliteManage.h"
#include "parsejson.h"
#include "global.h"

class designTab : public QDialog{
    Q_OBJECT
public:
    designTab(QJsonObject obj, QWidget *parent = 0);
    ~designTab(){}

public slots:
    void slot_saveAllButton(bool);
    void slot_sliderValueChange(int);

private:
    //!first tab widget function
    void initSetupCom();
    bool frequencySetting();
    bool farFieldSetting();
    void setFirstTabLayout();
    //!
    //!second tab widget function
    bool readDefaultVars();
    QComboBox* initUnitComBo();
    bool variablesSetting();
    QString getSliderSheet();
    //!
    QJsonObject saveInJsonObj();

    QTabWidget *tabWidget;
    QWidget *firstTab;
    QWidget *secondTab;
    QJsonObject obj;

    //frequencySetting
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
    QGroupBox *groupBoxFrequency;

    //farFieldSetting
    QLabel *thetaStartLabel;
    QLabel *thetaEndLabel;
    QLabel *thetaStepLabel;
    QLabel *phiStartLabel;
    QLabel *phiEndLabel;
    QLabel *phiStepLabel;
    QLineEdit *thetaStartEdit;
    QLineEdit *thetaEndEdit;
    QLineEdit *thetaStepEdit;
    QLineEdit *phiStartEdit;
    QLineEdit *phiEndEdit;
    QLineEdit *phiStepEdit;
    QGroupBox *groupBoxFarField;
    QPushButton *saveAllButton;

    //model variables setting
    QMap<QString, QString> defaultVars;
    QVector<varInfo> varinfos;
};

#endif // DESIGNTAB_H
