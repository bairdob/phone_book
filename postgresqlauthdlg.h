#ifndef POSTGRESQLAUTHDLG_H
#define POSTGRESQLAUTHDLG_H

#include <QDialog>
#include "ui_postgresqlauthdlg.h"

class PostgreSqlAuthDlg : public QDialog
{
	Q_OBJECT

public:
	PostgreSqlAuthDlg(QWidget *parent = 0);
	~PostgreSqlAuthDlg();
	bool authirizate();
	void LoadPrefs();
	void SavePrefs();
private:
	Ui::PostgreSqlAuthDlg ui;
private slots:
	void on_pushButton_accept_clicked();
};

#endif // POSTGRESQLAUTHDLG_H
