#ifndef WIZARDINTRODUCE_H
#define WIZARDINTRODUCE_H

#include <QtWidgets>
#include <QWizardPage>
#include "../Global/macrodefined.h"
#include "../Utility/sqliteManage.h"

class wizardIntroduce :public QWizardPage{
    Q_OBJECT
public:
    wizardIntroduce(QString antennaName, QWidget* parent = 0);
    ~wizardIntroduce();

    void setAtnIntroduceInfo(QString name);
private:
    QTextEdit *atnInfo;
    QLabel *atnPhoto;
    QString atnName;
    QString info;
    QString photo;
};

#endif
