#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QItemSelectionModel>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <surname.h>
#include <name.h>
#include <patromynic.h>
#include <street.h>
#include <database.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refreshData();
    QString surnameQueryGetId();
    QString nameQueryGetId();
    QString patronymicQueryGetId();
    QString streetQueryGetId();
    int getSurnameId(const QModelIndex &index);
    int getNameId(const QModelIndex &index);
    int getPatronymicId(const QModelIndex &index);
    int getStreetId(const QModelIndex &index);
    QString getUIdValue(const QModelIndex &index);
    QString getBuildingValue(const QModelIndex &index);
    QString getCorpusValue(const QModelIndex &index);
    QString getPhoneValue(const QModelIndex &index);

private slots:
    void on_toolButtonSurname_clicked();
    void on_toolButtonName_clicked();
    void on_toolButtonPatronymic_clicked();
    void on_toolButtonStreet_clicked();
    void on_toolButtonFind_clicked();
    void on_toolButtonRefresh_clicked();
    void on_toolButtonSave_clicked();
    void on_toolButtonAdd_clicked();
    void on_toolButtonDelete_clicked();
    void on_toolButtonPrint_clicked();
    void on_tableView_pressed(const QModelIndex &index);
    void on_actionSurname_triggered();
    void on_actionName_triggered();
    void on_actionPatronymic_triggered();
    void on_actionStreet_triggered();
    void refresh();

private:
    Ui::MainWindow *ui;
    Surname *surname_window;
    Name *name_window;
    Patromynic *patronymic_window;
    Street *street_window;
    Database database;
    QSqlQueryModel *model;
    QSqlRelationalTableModel * model2;
    QMap<QString, QString> userInput;
    QString selectRow;
};

#endif // MAINWINDOW_H
