#include "street.h"
#include "ui_street.h"


Street::Street(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Street)
{
    ui->setupUi(this);

    refreshData();
    //database.Connect();
    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged, this, &Street::cellChanged);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

Street::~Street()
{
    delete ui;
}

void Street::on_toolButtonExit_clicked()
{
    close();
}

void Street::on_toolButtonAdd_clicked()
{
    QSqlQuery getquery("SELECT max(street_id)  FROM street;");

    while (getquery.next()) {
           QSqlQuery query;
           int number = getquery.value(0).toInt() + 1;
           //qDebug() << number;
           query.prepare("INSERT INTO street(street_id) VALUES (:id);");
           query.bindValue(":id", number);
           query.exec();
    }

    refreshData();
}


void Street::on_tableView_pressed(const QModelIndex &index)
{
    selectRow = index.row() + 1;
    selectStr = index.sibling(index.row(),0).data().toString();
    qDebug() << selectRow << selectStr;
    //refreshData();
}


void Street::on_toolButtonDelete_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM street WHERE street_id = :id;");
    query.bindValue(":id", selectStr);
    query.exec();

    refreshData();
}

void Street::cellChanged(const QModelIndex &index){
//    QString new_street_value = ui->tableView->model()->data(index).toString();
//    int street_id = ui->tableView->selectionModel()->currentIndex().row()+1;
//    //qDebug() << ui->tableView->selectionModel()->currentIndex().row()+1 << new_sname_value;

//    QSqlQuery query;
//    query.prepare("UPDATE street SET street_value = :street where street_id = :id;");
//    query.bindValue(":street", new_street_value);
//    query.bindValue(":id", street_id);

//    if (query.exec()){
//        qDebug() << "Update success.";
//    } else {
//        qDebug() << "Update failed.";
//    }

//    refreshData();
}

void Street::refreshData(){
    model = new QSqlTableModel();
    model->setTable("street");
    model->setSort(0, Qt::AscendingOrder);
    model->select();
    ui->tableView->setModel(model);
}
