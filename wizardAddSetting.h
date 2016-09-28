#ifndef WIZARDADDSETTING_H
#define WIZARDADDSETTING_H

#include <QWizardPage>
#include <QtWidgets>
#include <fstream>
#include <QRegExp>
#include <QTextStream>

class wizardAddSetting :public QWizardPage
{
	Q_OBJECT
public:
    wizardAddSetting(QString antennaName = NULL, QWidget *parent = 0);
    ~wizardAddSetting(){}

    bool validatePage();
	QString readDefaultPath();
	void writeDefaultPath(QString path);
    bool isSettingDefaultPath() const;
    QString getProjectPath() const;
    QString getProjectName() const;

private:
    QLabel *hint;
    QLabel *projectName_label;
    QLineEdit *projectName_edit;
    QLabel *projectPath_label;
    QLineEdit *projectPath_edit;
    QPushButton *selectPath_btn;
    QRadioButton *alwaysPath;
    QString projectPath;
    QString projectName;

public slots:
    void slot_selectPath();
    void slot_giveHintName(QString);
};

#endif
