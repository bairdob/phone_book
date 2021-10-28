#include "name.h"
#include "ui_name.h"
#include "database.h"


Name::Name(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Name)
{
    ui->setupUi(this);

    refreshData();
    //database.Connect();
    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged, this, &Name::cellChanged);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);

}

Name::~Name()
{
    delete ui;
}

void Name::on_toolButtonExit_clicked()
{
    close();
}

void Name::on_toolButtonAdd_clicked()
{
    QSqlQuery getquery("SELECT max(name_id)  FROM name;");

    while (getquery.next()) {
           QSqlQuery query;
           int number = getquery.value(0).toInt() + 1;
           //qDebug() << number;
           query.prepare("INSERT INTO name(name_id) VALUES (:id);");
           query.bindValue(":id", number);
           query.exec();
    }

    refreshData();
}

void Name::on_tableView_pressed(const QModelIndex &index)
{
    selectRow = index.row() + 1;
    selectStr = index.sibling(index.row(),0).data().toString();
    qDebug() << selectRow << selectStr;
    //refreshData();
}

void Name::on_toolButtonDelete_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM name WHERE name_id = :id;");
    query.bindValue(":id", selectStr);
    query.exec();

    refreshData();
}

void Name::cellChanged(const QModelIndex &index){
//    QString new_name_value = ui->tableView->model()->data(index).toString();
//    int name_id = ui->tableView->selectionModel()->currentIndex().row()+1;
//    //qDebug() << ui->tableView->selectionModel()->currentIndex().row()+1 << new_sname_value;

//    QSqlQuery query;
//    query.prepare("UPDATE name SET name_value = :name where name_id = :id;");
//    query.bindValue(":name", new_name_value);
//    query.bindValue(":id", name_id);

//    if (query.exec()){
//        qDebug() << "Update success.";
//    } else {
//        qDebug() << "Update failed.";
//    }

//    refreshData();
}

void Name::refreshData(){
    model = new QSqlTableModel();
    model->setTable("name");
    model->setSort(0, Qt::AscendingOrder);
    model->select();
    ui->tableView->setModel(model);
}
