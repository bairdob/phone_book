#ifndef STREET_H
#define STREET_H

#include <database.h>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QAbstractItemModel>


namespace Ui {
class Street;
}

class Street : public QDialog
{
    Q_OBJECT

public:
    explicit Street(QWidget *parent = nullptr);
    ~Street();

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
    Ui::Street *ui;
    QSqlTableModel *model;
    QString selectStr;
    int selectRow;
};

#endif // STREET_H
