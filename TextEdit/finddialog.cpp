#include "finddialog.h"
#include "ui_finddialog.h"
#include "mainwindow.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromLocal8Bit("查找"));

    findLineEdit = new QLineEdit(this);
    QPushButton *btn = new QPushButton(QString::fromLocal8Bit("查找下一个"), this);
    QVBoxLayout *layOut = new QVBoxLayout(this);
    layOut->addWidget(findLineEdit);
    layOut->addWidget(btn);
    connect(btn, &QPushButton::clicked, dynamic_cast<MainWindow*>(this->parent()), &MainWindow::showFindText);
}

FindDialog::~FindDialog()
{
    delete ui;
}

const QString FindDialog::getLineEditText() const
{
    return findLineEdit->text();
}
