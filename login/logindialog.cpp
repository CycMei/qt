#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    if (ui->usrLineEdit->text().trimmed() == tr("cyc")
            && ui->pwdLineEdit->text() == tr("123456")){
            accept();
    }
    else{
        QString war = QString::fromLocal8Bit("警告");
         QString mes = QString::fromLocal8Bit("用户名和密码错误");
        QMessageBox::warning(this, war, mes, QMessageBox::Yes);

        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }

}
