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
    QJsonObject saveInJsonObj();

protected:
    bool validatePage();

private:
    void setAlgComboItem(QString name);
    QString setPath(QString name, bool flag = proPy);
    void initLayout();

    //QJsonObject obj;
    QString atnName;
    QLabel *proLabel;
    QLabel *algLabel;
    QLineEdit *atnLine;
    QComboBox *algCombo;
    QString proPath;
    QString algPath;
    QLabel *hint;
};

#endif // WIZARDOPTIMIZEALG_H
