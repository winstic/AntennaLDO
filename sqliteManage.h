#ifndef SQLITEMANAGE_H
#define SQLITEMANAGE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
class sqliteManage
{
public:
    sqliteManage();
    ~sqliteManage(){db.close();}

    QSqlDatabase getDataBase();
private:
    bool connect(QString &dbName);

    QSqlDatabase db;
};

#endif
