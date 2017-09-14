#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *queryBtn = new QPushButton(this);
    queryBtn->setText(QString::fromLocal8Bit("查询"));
    queryBtn->setGeometry(QRect(50, 50, 50, 30));
    connect(queryBtn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.exec("select * from student");
    while (query.next()) {
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString();
    }
}
