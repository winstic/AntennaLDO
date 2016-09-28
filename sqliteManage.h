#ifndef SQLITEMANAGE_H
#define SQLITEMANAGE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mybtn.h"
class sqliteManage
{
public:
    sqliteManage();
    ~sqliteManage(){db.close();}

    QSqlDatabase getDataBase();
private:
    bool connect(QString &dbName);

    QSqlDatabase db;
    //QSqlQuery *m_sqlQuery;
    /*QList<QString> m_antennaBtn_list;
	QList<QString> m_antennaName_list;
	QList<QString> m_antennaEngName_list;
	QList<QString> m_antennaDoc_list;
    QList<QString> m_antennaInfo_list;*/
};

#endif
