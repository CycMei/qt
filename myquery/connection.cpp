#include "connection.h"

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()){
        QMessageBox::critical(0, qApp->tr("cannot open database"),
                              qApp->tr("unable to eatabish a database connection"),
                              QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    query.exec("create table student (id int primary key,name varchar(20))");
    query.exec("insert into student values(0,'first')");
    query.exec("insert into student values(1,'second')");
    query.exec("insert into student values(2,'third')");
    query.exec("insert into student values(3,'fouth')");
    query.exec("insert into student values(4,'fifth')");
    return true;
}
