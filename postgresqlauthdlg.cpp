#include "postgresqlauthdlg.h"
#include "global.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>


QString sConfigFilePath = qApp->applicationDirPath()+"/database.cfg";

PostgreSqlAuthDlg::PostgreSqlAuthDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	LoadPrefs();
}

PostgreSqlAuthDlg::~PostgreSqlAuthDlg()
{

}

bool PostgreSqlAuthDlg::authirizate()
{
	::sGLobalSchemaDot.clear();

	::sCurrentDatabaseType = "QPSQL";
	QSqlDatabase db = QSqlDatabase::addDatabase(::sCurrentDatabaseType);
	
	db.setHostName(ui.lineEdit_host->text());
	db.setPort(ui.spinBox->value());
	db.setUserName(ui.lineEdit_username->text());
	db.setPassword(ui.lineEdit_passw->text());

	db.setDatabaseName(ui.lineEdit_base->text());
	bool login = db.open();
	if(db.lastError().isValid()){
		QMessageBox::information(this, "", db.lastError().text());
	}	
	return login;
}

void PostgreSqlAuthDlg::LoadPrefs()
{
	QFile file(sConfigFilePath);
	if(file.open(QIODevice::ReadOnly)){
		QStringList lst = QString().append(file.readAll()).split("\n");
		if(lst.count()>=4){
			QString sDatabase = lst.at(2);
			QString sHostname = lst.at(0);
			QString sPort = lst.at(1);
			QString sUsername = lst.at(3);
			
			ui.lineEdit_base->setText(sDatabase);
			ui.lineEdit_host->setText(sHostname);
			ui.lineEdit_username->setText(sUsername);
			ui.spinBox->setValue(sPort.toInt());
			if(lst.count()==5){
				ui.lineEdit_passw->setText( lst.at(4) );
				ui.checkBox_savePass->setChecked(true);
				authirizate();
			}
		}
		file.close();			
	}
}

void PostgreSqlAuthDlg::SavePrefs()
{
	QFile f(sConfigFilePath);
	if(f.open(QIODevice::WriteOnly)){
		QStringList lstValues;
		lstValues << ui.lineEdit_host->text() 
		<< QString::number(ui.spinBox->value())
		<< ui.lineEdit_base->text()
		<< ui.lineEdit_username->text();
		if(ui.checkBox_savePass->isChecked()) lstValues << ui.lineEdit_passw->text();

        //f.write(QByteArray().append(lstValues.join("\n")));

		f.close();
	}	else {
        //QMessageBox::information(this, "", tr("Failed to open config file!") );
	}
}


void PostgreSqlAuthDlg::on_pushButton_accept_clicked()
{
	if(authirizate()){
		SavePrefs();
		accept();
	}
}
