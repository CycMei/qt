#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QLabel"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), btClose(nullptr),
    showMainWindwo2Btb(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel *label = new QLabel(this);
    label->setText("hello world");
    label->setGeometry(QRect(50,50,200,25));

    this->setWindowTitle("qt5.1 窗体应用");
    this->setMaximumSize(300,300);
    this->setMinimumSize(300,300);

    this->move(0,0);
    this->setStyleSheet("background:red");

    this->setWindowIcon(QIcon(":/new/prefix1/ico"));

//    this->setWindowFlag(Qt::FramelessWindowHint);

    this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
    this->setWindowFlags(Qt::WindowCloseButtonHint);


    btClose = new QPushButton(this);
    btClose->setText("关闭");
    connect(btClose, SIGNAL(clicked()), this, SLOT(close()));


    showMainWindwo2Btb = new QPushButton(this);
    showMainWindwo2Btb->setGeometry(QRect(50,50,100,25));
    showMainWindwo2Btb->setText("显示窗体2");
    connect(showMainWindwo2Btb, SIGNAL(clicked(bool)), this, SLOT(showMainWindow2()));


}

void MainWindow::mousePressEvent(QMouseEvent *e){
    last = e->globalPos();
    std::cout << "(x, y) : " << last.x() << ", "<< last.y() << std::endl;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x() + dx, y() + dy);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x() + dx, y() + dy);
}


void MainWindow::showMainWindow2() {
    w2.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
