#include "database.h"
#include "surname.h"
#include "ui_surname.h"


Surname::Surname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Surname)
{
    ui->setupUi(this);
    refreshData();
    //database.Connect();
    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged, this, &Surname::cellChanged);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

Surname::~Surname()
{
    delete ui;
}

void Surname::on_toolButtonExit_clicked()
{
    close();
}

void Surname::on_toolButtonAdd_clicked()
{
    QSqlQuery getquery("SELECT max(sname_id)  FROM surname;");

    while (getquery.next()) {
           QSqlQuery query;
           int number = getquery.value(0).toInt() + 1;
           //qDebug() << number;
           query.prepare("INSERT INTO surname(sname_id) VALUES (:id);");
           query.bindValue(":id", number);
           query.exec();
    }

    refreshData();
}

void Surname::on_tableView_pressed(const QModelIndex &index)
{
    selectRow = index.row() + 1;
    selectStr = index.sibling(index.row(),0).data().toString();
    qDebug() << selectRow << selectStr;
    //refreshData();
}

void Surname::on_toolButtonDelete_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM surname WHERE sname_id = :id;");
    query.bindValue(":id", selectStr);
    query.exec();

    refreshData();
}

void Surname::cellChanged(const QModelIndex &index){
//    QString new_sname_value = ui->tableView->model()->data(index).toString();
//    int sname_id = ui->tableView->selectionModel()->currentIndex().row()+1;
//    //qDebug() << ui->tableView->selectionModel()->currentIndex().row()+1 << new_sname_value;

//    QSqlQuery query;
//    query.prepare("UPDATE surname SET sname_value = :name where sname_id = :id;");
//    query.bindValue(":name", new_sname_value);
//    query.bindValue(":id", sname_id);

//    if (query.exec()){
//        qDebug() << "Update success.";
//    } else {
//        qDebug() << "Update failed.";
//    }

//    refreshData();
}

void Surname::refreshData(){
    model = new QSqlTableModel();
    model->setTable("surname");
    model->setSort(0, Qt::AscendingOrder);
    model->select();
    ui->tableView->setModel(model);
}
