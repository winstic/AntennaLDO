#include "sqliteManage.h"
sqliteManage::sqliteManage(){
    db = QSqlDatabase::addDatabase(("QSQLITE"));
    QString dbname = "antenna.db";
    connect(dbname);
}

bool sqliteManage::connect(QString &dbName){
    db.setDatabaseName(dbName);
    //QMessageBox::information(this, "infomation", "test my openAction");
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"), QString("sqliteManage.cpp:12: error: %1").arg(db.lastError().text()));
        return false;
    }
    return true;
}

QSqlDatabase sqliteManage::getDataBase(){
    return db;
}



