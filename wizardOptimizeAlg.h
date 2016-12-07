#ifndef WIZARDOPTIMIZEALG_H
#define WIZARDOPTIMIZEALG_H

#include <QtWidgets>
#include <QWizardPage>
//#include "parsejson.h"
#include "sqliteManage.h"
#include "macrodefined.h"
#include "global.h"
#include "parsejson.h"

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
    void confSetting();
    void initLayout();

    //QJsonObject obj;
    QString atnName;
    QString algName;
    QString proPath;
    QString algPath;
    QLabel *hint;

    QLabel *algLabel;
    QLabel *generationLabel;
    QLabel *popsizeLabel;
    QLabel *threadLabel;
    QComboBox *algCombo;
    QLineEdit *generationLine;
    QLineEdit *popsizeLine;
    QLineEdit *threadLine;
};

#endif // WIZARDOPTIMIZEALG_H
