#include "global.h"
#include "postgresqlauthdlg.h"
//#include "oracleauthdlg.h"
//#include "mysqlauthdlg.h"
#include <QString>
#include <QSqlDatabase>

QString sGLobalSchemaDot;
int iGlobalLangId;
QString sCurrentDatabaseType;

bool connectDatabase()
{
	bool bResult = false;
	
	//if last connection is ok, remove all there
	if(QSqlDatabase::database().driverName()!=::sCurrentDatabaseType){
		//here do some actions	
	}
	
	if(QSqlDatabase::database().isOpen())
		QSqlDatabase::database().close();

	if(::sCurrentDatabaseType == "QOCI"){
//		OracleAuthDlg * dlg = new OracleAuthDlg();
//		if(!QSqlDatabase::database().isOpen()) bResult = dlg->exec();
//		else bResult = true;
//		delete dlg;
	}else if(::sCurrentDatabaseType == "QPLSQL"){
		PostgreSqlAuthDlg * dlg = new PostgreSqlAuthDlg();
		if(!QSqlDatabase::database().isOpen()) bResult = dlg->exec();
		else bResult = true;
		delete dlg;
	}else{
//		MysqlAuthDlg * dlg = new MysqlAuthDlg();
//		if(!QSqlDatabase::database().isOpen()) bResult = dlg->exec();
//		else bResult = true;
//		delete dlg;
	}
	
	return bResult;
}
