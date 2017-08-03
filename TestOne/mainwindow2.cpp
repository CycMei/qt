#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "logindlg.h"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setStyleSheet("background-image:url(:/new/prefix1/yuanliang);background-repeat:no-repeat;");





}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_pushButton_clicked()
{
    QDialog *dlg = new QDialog(this);
    dlg->show();
}
