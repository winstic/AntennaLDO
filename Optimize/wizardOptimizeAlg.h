#ifndef WIZARDOPTIMIZEALG_H
#define WIZARDOPTIMIZEALG_H

#include <QtWidgets>
#include <QWizardPage>
#include <QUuid>
//#include "parsejson.h"
#include "../Global/global.h"
#include "../Global/macrodefined.h"
#include "../Utility/parsejson.h"
#include "../Utility/sqliteManage.h"

class wizardOptimizeAlg : public QWizardPage{
    Q_OBJECT

public:
    wizardOptimizeAlg(QWidget *parent = 0);
    ~wizardOptimizeAlg(){}
    QString getProPath() const;
    QString getAlgPath() const;
    QString getAlgName() const;
    QJsonObject saveInJsonObj();

protected:
    bool validatePage();
    void insert2table(QTableWidget *table, const int &row, const int &clomun, const QString &itemValue);

public slots:
    void slot_algName(const int index);
    void slot_singleCheckBoxStateChange(const int state);
    void slot_multiCheckBoxStateChange(const int state);
    void slot_addNodeButton(/*bool check*/);
    void slot_delNodeButton(/*bool check*/);

private:
    void setAlgComboItem(QString name);
    QString setPath(QString name, bool flag = proPy);
    void confSetting();
    void initLayout();

    //QJsonObject obj;
    QString atnName;
    QString algName;
    QString proPath;
    QString algPath;

    QLabel *algLabel;
    QComboBox *algCombo;

    QTableWidget *varTable;
    enum VARCOLUMN{keyFlag = 0, valueFlag};


    QLabel *threadLabel;
    QLineEdit *threadLine;
    QCheckBox *singleComp;

    QTableWidget *nodesTable;
    enum NODESCOLUMN{nodeFlag = 0, coreFlag};

    QLabel *nodeLabel;
    QLabel *coreLabel;
    QLineEdit *nodeEdit;
    QLineEdit *coreEdit;
    QPushButton *addButton;
    QPushButton *delButton;

    QCheckBox *multiComp;
    QGroupBox *singleGroup;
    QGroupBox *multiGroup;
    QLabel *hint;
};

#endif // WIZARDOPTIMIZEALG_H
