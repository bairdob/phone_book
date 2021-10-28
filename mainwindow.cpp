#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "surname.h"
#include "name.h"
#include "patromynic.h"
#include "street.h"
#include "database.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database.connect();

    if (database.open()){
          refreshData();
    }
    else {
        QMessageBox::information(this, "failed", "Connection failed");
    }
}

MainWindow::~MainWindow()
{
    //database.close();
    delete ui;
}

void MainWindow::on_toolButtonSurname_clicked()
{
    surname_window = new Surname(this);
    surname_window->show();
}

void MainWindow::on_toolButtonName_clicked()
{
    name_window = new Name(this);
    name_window->show();
}

void MainWindow::on_toolButtonPatronymic_clicked()
{
    patronymic_window = new Patromynic(this);
    patronymic_window->show();
}

void MainWindow::on_toolButtonStreet_clicked()
{
    street_window = new Street(this);
    street_window->show();
}

void MainWindow::on_actionSurname_triggered()
{
    surname_window = new Surname(this);
    surname_window->show();
}

void MainWindow::on_actionName_triggered()
{
    name_window = new Name(this);
    name_window->show();
}

void MainWindow::on_actionPatronymic_triggered()
{
    patronymic_window = new Patromynic(this);
    patronymic_window->show();
}

void MainWindow::on_actionStreet_triggered()
{
    street_window = new Street(this);
    street_window->show();
}

void MainWindow::on_toolButtonFind_clicked()
{
    QString str = "SELECT main.u_id AS u_id, surname.sname_value AS surname, \
                        name.name_value AS name, patronymic.patr_value AS patronymic, \
                        street.street_value AS street, main.building as building, \
                        main.corpus AS corpus, phone AS phone \
                    FROM main \
                    JOIN patronymic ON main.patronymic = patronymic.patr_id \
                    JOIN surname ON main.surname = surname.sname_id \
                    JOIN street ON main.street = street.street_id \
                    JOIN name ON main.name = name.name_id WHERE TRUE";

    if (ui->comboBoxSurname->currentText() != ""){
        str += " AND surname = " + surnameQueryGetId();
    }

    if (ui->comboBoxName->currentText() != ""){
        str += " AND name = " + nameQueryGetId();
    }

    if (ui->comboBoxPatronymic->currentText() != ""){
        str += " AND patronymic = " + patronymicQueryGetId();
    }

    if (ui->comboBoxStreet->currentText() != ""){
        str += " AND patronymic = " + streetQueryGetId();
    }

    if (ui->lineEditBuilding->text()!=""){
        str += " AND building = '" + ui->lineEditBuilding->text() +"'";
    }

    if (ui->lineEditCorpus->text()!=""){
        str += " AND corpus = '" + ui->lineEditCorpus->text() +"'";
    }

    if (ui->lineEditPhone->text()!=""){
        str += " AND phone = '" + ui->lineEditPhone->text() +"'";
    }

    qDebug() << str;
    model = new QSqlQueryModel();
    model->setQuery(str + ";");
    ui->tableView->setModel(model);
}

QString MainWindow::surnameQueryGetId(){
    QSqlQuery query;
    query.prepare("SELECT * FROM surname WHERE sname_value = :surname;");
    query.bindValue(":surname", ui->comboBoxSurname->currentText());
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString MainWindow::nameQueryGetId(){
    QSqlQuery query;
    query.prepare("SELECT * FROM name WHERE name_value = :name;");
    query.bindValue(":name", ui->comboBoxName->currentText());
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString MainWindow::patronymicQueryGetId(){
    QSqlQuery query;
    query.prepare("SELECT * FROM patronymic WHERE patr_value = :name;");
    query.bindValue(":name", ui->comboBoxPatronymic->currentText());
    query.exec();
    query.first();
    return query.value(0).toString();
}

QString MainWindow::streetQueryGetId(){
    QSqlQuery query;
    query.prepare("SELECT * FROM street WHERE street_value = :street;");
    query.bindValue(":street", ui->comboBoxStreet->currentText());
    query.exec();
    query.first();
    return query.value(0).toString();
}

void MainWindow::on_toolButtonRefresh_clicked()
{
    refreshData();
}

void MainWindow::refreshData(){

//    // classic query
//    model = new QSqlQueryModel();
//    model->setQuery("SELECT surname.sname_value AS surname, name.name_value AS name, \
//                    patronymic.patr_value AS patronymic, street.street_value AS street, phone AS PHONE \
//                    FROM main \
//                    JOIN patronymic ON main.patronymic = patronymic.patr_id \
//                    JOIN surname ON main.surname = surname.sname_id \
//                    JOIN street ON main.street = street.street_id \
//                    JOIN name ON main.name = name.name_id;");
//    ui->tableView->setModel(model);

    model2 = new QSqlRelationalTableModel();
    model2->setTable("main");
    model2->setRelation(1, QSqlRelation("surname", "sname_id", "sname_value"));
    model2->setRelation(2, QSqlRelation("name", "name_id", "name_value"));
    model2->setRelation(3, QSqlRelation("patronymic", "patr_id", "patr_value"));
    model2->setRelation(4, QSqlRelation("street", "street_id", "street_value"));
    model2->select();

//    ui->tableView->resizeRowsToContents();
//    ui->tableView->resizeColumnsToContents();
    ui->tableView->setModel(model2);

    model = new QSqlQueryModel();
    model->setQuery("SELECT sname_value AS name FROM surname;");
    ui->comboBoxSurname->setPlaceholderText(QStringLiteral("(Surname)"));
    ui->comboBoxSurname->setModel(model);
    ui->comboBoxSurname->setCurrentIndex(-1);

    model = new QSqlQueryModel();
    model->setQuery("SELECT name_value AS familiya FROM name;");
    ui->comboBoxName->setPlaceholderText(QStringLiteral("(Name)"));
    ui->comboBoxName->setModel(model);
    ui->comboBoxName->setCurrentIndex(-1);

    model = new QSqlQueryModel();
    model->setQuery("SELECT patr_value AS patronymic FROM patronymic;");
    ui->comboBoxPatronymic->setPlaceholderText(QStringLiteral("(Patronymic)"));
    ui->comboBoxPatronymic->setModel(model);
    ui->comboBoxPatronymic->setCurrentIndex(-1);

    model = new QSqlQueryModel();
    model->setQuery("SELECT street_value AS name FROM street;");
    ui->comboBoxStreet->setPlaceholderText(QStringLiteral("(Street)"));
    ui->comboBoxStreet->setModel(model);
    ui->comboBoxStreet->setCurrentIndex(-1);

    ui->lineEditBuilding->setText("");
    ui->lineEditCorpus->setText("");
    ui->lineEditPhone->setText("");
}

void MainWindow::on_toolButtonSave_clicked()
{
    QString str = "UPDATE main SET ";
    if (ui->comboBoxSurname->currentText() != ""){
        str += "surname = " + surnameQueryGetId() + ", ";
    };

    if (ui->comboBoxName->currentText() != ""){
        str += "name = " + nameQueryGetId() + ", ";
    };

    if (ui->comboBoxPatronymic->currentText() != ""){
        str += "patronymic = " + patronymicQueryGetId() + ", ";
    };

    if (ui->comboBoxStreet->currentText() != ""){
        str += "street = " + streetQueryGetId() + ", ";
    };

    if (ui->lineEditBuilding->text()!=""){
        str += "building = '" + ui->lineEditBuilding->text() + "', ";
    } else {
        str += "NULL, ";
    };

    if (ui->lineEditCorpus->text()!=""){
        str += "corpus = '"+ ui->lineEditCorpus->text() + "', ";
    } else {
        str += "NULL, ";
    };

    if (ui->lineEditPhone->text()!=""){
        str += "phone = '" + ui->lineEditPhone->text() +"'";
    } else {
        str += "NULL ";
    }

    str += " WHERE u_id = " + selectRow;

    model = new QSqlQueryModel();
    model->setQuery(str + ";");
    ui->tableView->setModel(model);
    refreshData();

    qDebug() << str;
}


void MainWindow::on_toolButtonAdd_clicked()
{
    QString str = "INSERT INTO main(surname, name, patronymic, street, building, corpus, phone) \
                   VALUES (";
    if (ui->comboBoxSurname->currentText() != ""){
        str += surnameQueryGetId() + ",";
    } else {
        str += "NULL,";
    }

    if (ui->comboBoxName->currentText() != ""){
        str += nameQueryGetId() + ",";
    } else {
        str += "NULL, ";
    }

    if (ui->comboBoxPatronymic->currentText() != ""){
        str += patronymicQueryGetId() + ",";
    } else {
        str += "NULL, ";
    }

    if (ui->comboBoxStreet->currentText() != ""){
        str += streetQueryGetId() + ",";
    } else {
        str += "NULL, ";
    }

    if (ui->lineEditBuilding->text()!=""){
        str += "'" + ui->lineEditBuilding->text() + "',";
    } else {
        str += "NULL, ";
    }

    if (ui->lineEditCorpus->text()!=""){
        str += "'" + ui->lineEditCorpus->text() + "',";
    } else {
        str += "NULL, ";
    }

    if (ui->lineEditPhone->text()!=""){
        str += "'" + ui->lineEditPhone->text() + "')";
    } else {
        str += "NULL)";
    }

    model = new QSqlQueryModel();
    model->setQuery(str + ";");
    ui->tableView->setModel(model);
    refreshData();

    qDebug() << str;
}


void MainWindow::on_tableView_pressed(const QModelIndex &index)
{
    selectRow = getUIdValue(index);
    ui->comboBoxSurname->setCurrentIndex(getSurnameId(index));
    ui->comboBoxName->setCurrentIndex(getNameId(index));
    ui->comboBoxPatronymic->setCurrentIndex(getPatronymicId(index));
    ui->comboBoxStreet->setCurrentIndex(getStreetId(index));
    ui->lineEditBuilding->setText(getBuildingValue(index));
    ui->lineEditCorpus->setText(getCorpusValue(index));
    ui->lineEditPhone->setText(getPhoneValue(index));
}

QString MainWindow::getUIdValue(const QModelIndex &index){
    return index.sibling(index.row(),0).data().toString();
}

int MainWindow::getSurnameId(const QModelIndex &index){
    return ui->comboBoxSurname->findText(index.sibling(index.row(),1).data().toString());
}

int MainWindow::getNameId(const QModelIndex &index){
    return ui->comboBoxName->findText(index.sibling(index.row(),2).data().toString());
}

int MainWindow::getPatronymicId(const QModelIndex &index){
    return ui->comboBoxPatronymic->findText(index.sibling(index.row(),3).data().toString());
}

int MainWindow::getStreetId(const QModelIndex &index){
    return ui->comboBoxStreet->findText(index.sibling(index.row(),4).data().toString());
}

QString MainWindow::getBuildingValue(const QModelIndex &index){
    return index.sibling(index.row(),5).data().toString();
}

QString MainWindow::getCorpusValue(const QModelIndex &index){
    return index.sibling(index.row(),6).data().toString();
}

QString MainWindow::getPhoneValue(const QModelIndex &index){
    return index.sibling(index.row(),7).data().toString();
}

void MainWindow::on_toolButtonDelete_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM main WHERE u_id = :id;");
    query.bindValue(":id", selectRow);
    query.exec();
    refreshData();
}


void MainWindow::on_toolButtonPrint_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("phone_book")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}



