#include "logindlg.h"
#include "ui_logindlg.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);


    QString str = QString::fromLocal8Bit("新窗口");
    ui->pushButton->setText(str);

}

LoginDlg::~LoginDlg()
{
    delete ui;
}
