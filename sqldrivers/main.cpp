#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    qDebug() << "Available drivers: ";
//    QStringList drivers = QSqlDatabase::drivers();
//    foreach (QString driver, drivers) {
//        qDebug() << driver;
//    }



    QSqlDatabase ddb = QSqlDatabase::addDatabase("QMYSQL");
    ddb.setHostName("localhost");
    ddb.setDatabaseName("mydata");
    ddb.setUserName("root");
    ddb.setPassword("root");
    if (!ddb.open())
        qDebug() <<"failed to connect to root mysql admin ";
    else
        qDebug() << "open ";
    QSqlQuery ddbQuery(ddb);
    ddbQuery.exec("create table student(id int primary key, name varchar(20))");
    ddbQuery.exec("insert into student values(1, 'xiaogang')");
    ddbQuery.exec("insert into student values(2, 'xiaoming')");
    ddbQuery.exec("insert into student values(3, 'xiaohong')");
    ddbQuery.exec("select id,name from student where id >= 2");
    while (ddbQuery.next()) {
        int value0 = ddbQuery.value(0).toInt();
        QString value1 = ddbQuery.value(1).toString();
        qDebug() <<value0 << value1;
    }






    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open())
        return false;
    QSqlQuery query;
    query.exec("create table student(id int primary key, name varchar)");
    query.exec("insert into student values(1, 'xiaogang')");
    query.exec("insert into student values(2, 'xiaoming')");
    query.exec("insert into student values(3, 'xiaohong')");
    query.exec("select id, namefro smtudent where id >= 2");
    while (query.next()) {
        int value0 = query.value(0).toInt();
        QString value1 = query.value(1).toString();
        qDebug() << value0 << value1;
    }

    return a.exec();
}
