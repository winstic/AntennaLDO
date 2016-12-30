#ifndef DESIGNTAB_H
#define DESIGNTAB_H

#include <QtWidgets>
#include <QVector>
#include "macrodefined.h"
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
    void slot_LinetextChange(QString text);
    void slot_sliderValueChange(QString);
    void slot_unitchange(QString);

private:
    //!first tab widget function
    void initSetupCom();
    bool frequencySetting();
    bool farFieldSetting();
    void setFirstTabLayout();
    //!
    //!second tab widget function
    void tableSetting();
    bool readDefaultVars();
    void initUnitComBo(QComboBox* comb);
    bool variablesSetting();
    QString getSliderSheet();
    double unitConversion(double sourceData, int preunit, int curunit);
    void insert2table(const int &row, const int &clomun, const QString &itemValue);
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
    QTableWidget *varTable;
    QMap<int, int> comboDatas;      //save combobox data
    QSignalMapper *signalsmapSlider;  //use signalmaper manage signals in table
    QSignalMapper *signalsmapUnit;  //use signalmaper manage signals in table
    enum VARCOLUMN{varnote = 0, varvalue, varunit};
    //QVector<varInfo> varinfos;
};

#endif // DESIGNTAB_H
