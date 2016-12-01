#ifndef WIZARDOPTIMIZEALG_H
#define WIZARDOPTIMIZEALG_H

#include <QtWidgets>
#include <QWizardPage>
//#include "parsejson.h"
#include "sqliteManage.h"
#include "macrodefined.h"
#include "global.h"

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

public slots:
    void slot_algName(const int index);

private:
    void setAlgComboItem(QString name);
    QString setPath(QString name, bool flag = proPy);
    void initLayout();

    //QJsonObject obj;
    QString atnName;
    QString algName;
    QLabel *proLabel;
    QLabel *algLabel;
    QLineEdit *atnLine;
    QComboBox *algCombo;
    QString proPath;
    QString algPath;
    QLabel *hint;
};

#endif // WIZARDOPTIMIZEALG_H
