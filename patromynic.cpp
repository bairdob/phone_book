#include "patromynic.h"
#include "ui_patromynic.h"
#include "database.h"


Patromynic::Patromynic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Patromynic)
{
    ui->setupUi(this);

    refreshData();
    //database.Connect();
    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged, this, &Patromynic::cellChanged);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

Patromynic::~Patromynic()
{
    delete ui;
}

void Patromynic::on_toolButtonExit_clicked()
{
    close();
}

void Patromynic::on_toolButtonAdd_clicked()
{
    QSqlQuery getquery("SELECT max(patr_id)  FROM patronymic;");

    while (getquery.next()) {
           QSqlQuery query;
           int number = getquery.value(0).toInt() + 1;
           //qDebug() << number;
           query.prepare("INSERT INTO patronymic(patr_id) VALUES (:id);");
           query.bindValue(":id", number);
           query.exec();
    }

    refreshData();
}


void Patromynic::on_tableView_pressed(const QModelIndex &index)
{
    selectRow = index.row() + 1;
    selectStr = index.sibling(index.row(),0).data().toString();
    qDebug() << selectRow << selectStr;
    //refreshData();
}


void Patromynic::on_toolButtonDelete_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM patronymic WHERE patr_id = :id;");
    query.bindValue(":id", selectStr);
    query.exec();

    refreshData();
}

void Patromynic::cellChanged(const QModelIndex &index){
//    QString new_patr_value = ui->tableView->model()->data(index).toString();
//    int patr_id = ui->tableView->selectionModel()->currentIndex().row()+1;
//    //qDebug() << ui->tableView->selectionModel()->currentIndex().row()+1 << new_sname_value;

//    QSqlQuery query;
//    query.prepare("UPDATE patronymic SET patr_value = :name where patr_id = :id;");
//    query.bindValue(":name", new_patr_value);
//    query.bindValue(":id", patr_id);

//    if (query.exec()){
//        qDebug() << "Update success.";
//    } else {
//        qDebug() << "Update failed.";
//    }

//    refreshData();
}

void Patromynic::refreshData(){
    model = new QSqlTableModel();
    model->setTable("patronymic");
    model->setSort(0, Qt::AscendingOrder);
    model->select();
    ui->tableView->setModel(model);
}
