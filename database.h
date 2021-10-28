#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>


class Database
{
private:
    QSqlDatabase database;
public:
    Database();
    void connect();
    bool open();
    void close();
    ~Database();
};

#endif // DATABASE_H
