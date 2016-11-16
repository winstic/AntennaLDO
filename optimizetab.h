#ifndef OPTIMIZETAB_H
#define OPTIMIZETAB_H

#include <QtWidgets>
#include "sqliteManage.h"
#include "macrodefined.h"
#include "parsejson.h"
#include "global.h"

class optimizeTab : public QDialog{
    Q_OBJECT
public:
    optimizeTab(QJsonObject obj, QWidget *parent = 0);
    ~optimizeTab(){}
    //fourth tab
    QString getProPath() const;
    QString getAlgPath() const;

public slots:
    void slot_saveAllButton(bool);
    void slot_gainChangeOptimaltype(QString);
    void slot_axialChangeOptimaltype(QString);
    void slot_lossChangeType(QString);
    void slot_unitchange(QString);

private:
    //!first tab widget function
    void initSetupCom();
    bool frequencySetting();
    bool farFieldSetting();
    void setFirstTabLayout();
    //!
    //!second tab widget function
    bool gainSetting();
    bool axialSetting();
    bool lossSetting();
    void initOptimalTypeComBox(QComboBox *combox);
    void initLossTypeComBox(QComboBox *combox);
    void setSecondTabLayout();
    //!

    //!third tab widget function
    bool wizardDialog();
    double unitConversion(double sourceData, int preunit, int curunit);
    void initUnitComBo(QComboBox *comb);
    //!

    //!fourth tab wodget function
    void setAlgComboItem(QString name);
    QString setPath(QString name, bool flag = proPy);
    void setFourthTabLayout();
    //!

    void insert2table(QTableWidget *table, const int &row, const int &clomun, const QString &itemValue);
    QJsonObject saveInJsonObj();

    QTabWidget *tabWidget;
    QWidget *firstTab;
    QWidget *secondTab;
    QWidget *thirdTab;
    QWidget *fourthTab;
    QJsonObject obj;
    QPushButton *saveAllButton;

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

    //gain axial loss setting
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

    //variables setting
    QTableWidget *varTable;
    QMap<int, int> comboDatas;
    QSignalMapper *signalsmap;  //use signalmaper manage signals in table
    enum VARCOLUMN{varnote = 0, varmin, varmax, varunit};

    //algorithm setting
    QString atnName;
    QLabel *proLabel;
    QLabel *algLabel;
    QLineEdit *atnLine;
    QComboBox *algCombo;
    QString proPath;
    QString algPath;
};

#endif // OPTIMIZETAB_H
