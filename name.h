#ifndef NAME_H
#define NAME_H

#include <database.h>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QAbstractItemModel>


namespace Ui {
class Name;
}

class Name : public QDialog
{
    Q_OBJECT

public:
    explicit Name(QWidget *parent = nullptr);
    ~Name();

private slots:
    void on_toolButtonExit_clicked();
    void on_toolButtonAdd_clicked();
    void on_toolButtonDelete_clicked();
    void on_tableView_pressed(const QModelIndex &index);
    void refreshData();
    void cellChanged(const QModelIndex &index);

private:
    Ui::Name *ui;
    QSqlTableModel *model;
    QString selectStr;
    int selectRow;
};

#endif // NAME_H
