#ifndef PATROMYNIC_H
#define PATROMYNIC_H

#include <database.h>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QAbstractItemModel>


namespace Ui {
class Patromynic;
}

class Patromynic : public QDialog
{
    Q_OBJECT

public:
    explicit Patromynic(QWidget *parent = nullptr);
    ~Patromynic();

private slots:
    void on_toolButtonExit_clicked();
    void on_toolButtonAdd_clicked();
    void on_toolButtonDelete_clicked();
    void on_tableView_pressed(const QModelIndex &index);
    void refreshData();
    void cellChanged(const QModelIndex &index);

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::Patromynic *ui;
    QSqlTableModel *model;
    QString selectStr;
    int selectRow;
};

#endif // PATROMYNIC_H
