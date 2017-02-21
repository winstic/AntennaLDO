#ifndef MODELFILE_H
#define MODELFILE_H

#include <QtWidgets>
#include "../Global/global.h"
#include "sqliteManage.h"

class modelFile : public QDialog{
    Q_OBJECT
public:
    modelFile(QString antennaName, QWidget *parent = 0);
    ~modelFile(){}
private:
    QString getAtnModelInfo(const QString name);

    QTextEdit *atnInfo;
    QString atnName;
    QString info;
};

#endif // MODELFILE_H
