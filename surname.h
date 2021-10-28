#ifndef SURNAME_H
#define SURNAME_H

#include <database.h>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QAbstractItemModel>


namespace Ui {
class Surname;
}

class Surname : public QDialog
{
    Q_OBJECT

public:
    explicit Surname(QWidget *parent = nullptr);
    ~Surname();

private slots:
    void on_toolButtonExit_clicked();
    void on_toolButtonAdd_clicked();
    void on_toolButtonDelete_clicked();
    void on_tableView_pressed(const QModelIndex &index);
    void refreshData();
    void cellChanged(const QModelIndex &index);

private:
    Ui::Surname *ui;
    QSqlTableModel *model;
    QString selectStr;
    int selectRow;
};

#endif // SURNAME_H
