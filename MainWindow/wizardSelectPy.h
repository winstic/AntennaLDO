#ifndef WIZARDSELECTPY_H
#define WIZARDSELECTPY_H

#include <QWizardPage>
#include <QtWidgets>
#include "../Global/macrodefined.h"
#include "../Utility/sqliteManage.h"

class wizardSelectPy :public QWizardPage
{
	Q_OBJECT
public:
    wizardSelectPy(QString antennaName, QWidget *parent = 0);
    ~wizardSelectPy(){}
	bool validatePage();
    QString setPath(QString name, bool flag = proPy);
    QString getProPath() const;
    QString getAlgPath() const;
    void setAlgComBoItem(QString name);

private:
    QString atnName;
    QLabel *proLabel;
    QLabel *algLabel;
    QLabel *hint;
    QComboBox *proCombo;
    QComboBox *algCombo;
    QString proPath;
    QString algPath;

    void initProCombo();

public slots:
    void slot_proName(int);
    void slot_algName(int);
};

#endif
