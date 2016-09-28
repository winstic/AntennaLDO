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
        QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
        return false;
    }
    return true;
}

QSqlDatabase sqliteManage::getDataBase(){
    return db;
}

/*void sqliteManage::LoadAllAntenna()
{
	//sqlOpen();
	QString sql;
	sql = "select  * from antennaProblem;";
	m_sqlQuery = new QSqlQuery();
	m_sqlQuery->exec(sql);
	while (m_sqlQuery->next())
	{
		m_antennaBtn_list.append(m_sqlQuery->value("pModelPath").toString());
		m_antennaDoc_list.append(m_sqlQuery->value("pDocPath").toString());
		m_antennaEngName_list.append(m_sqlQuery->value("pEngName").toString());
		m_antennaName_list.append(m_sqlQuery->value("pName").toString());
		m_antennaInfo_list.append(m_sqlQuery->value("pInfo").toString());
	}
	//m_db->close();
}
*/



