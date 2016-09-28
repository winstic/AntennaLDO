#ifndef WIZARDSELECTPY_H
#define WIZARDSELECTPY_H

#include <QWizardPage>
#include <QtWidgets>
#include "sqliteManage.h"
#include "global.h"

class wizardSelectPy :public QWizardPage
{
	Q_OBJECT
public:
    wizardSelectPy(QString antennaName, QWidget *parent = 0);
	bool validatePage();
    QString setPyPath(QString name, bool flag = 0);
    QString getProPyPath() const;
    QString getAlgPyPath() const;
    void setAlgComBoItem(QString name);

private:
    QString atnName;
    QLabel *proLabel;
    QLabel *algLabel;
    QLabel *hint;
    QComboBox *proCombo;
    QComboBox *algCombo;
	QString pro_py_path;
	QString alg_py_path;

    void initProCombo();

public slots:
    void slot_proName(int);
    void slot_algName(int);
};

#endif
