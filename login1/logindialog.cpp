#include "logindialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent){
    usrLabel = new QLabel(this);
    usrLabel->move(70, 80);
    QString strUsr = QString::fromLocal8Bit("用户名：");
    usrLabel->setText(strUsr);

    usrLineEdit = new QLineEdit(this);
    usrLineEdit->move(140, 80);
    QString strUsrHold = QString::fromLocal8Bit("请输入用户名");
    usrLineEdit->setPlaceholderText(strUsrHold);

    pwdLabel = new QLabel(this);
    pwdLabel->move(70, 130);
    QString strpwd = QString::fromLocal8Bit("密码：");
    pwdLabel->setText(strpwd);

    pwdLineEdit = new QLineEdit(this);
    pwdLineEdit->setEchoMode(QLineEdit::Password);
    pwdLineEdit->move(140, 130);
     QString strpwdHold = QString::fromLocal8Bit("请输入密码");
    pwdLineEdit->setPlaceholderText(strpwdHold);

    loginBtn = new QPushButton(this);
    loginBtn->move(50, 200);
     QString strlog = QString::fromLocal8Bit("登录");
    loginBtn->setText(strlog);

    exitBtn = new QPushButton(this);
    exitBtn->move(210, 200);
    QString strExit  = QString::fromLocal8Bit("退出");
    exitBtn->setText(strExit);

    connect(loginBtn, &QPushButton::clicked, this, &LoginDialog::login);
    connect(exitBtn, &QPushButton::clicked, this, &LoginDialog::close);
}


void LoginDialog::login(){
    if (usrLineEdit->text().trimmed() == tr("cyc")
            && pwdLineEdit->text() == tr("123456")){
        accept();
    }
    else{
        QString strTitle  = QString::fromLocal8Bit("警告");
        QString strMesg  = QString::fromLocal8Bit("用户名和密码错误");
        QMessageBox::warning(this, strTitle, strMesg, QMessageBox::Yes);
        usrLineEdit->clear();
        pwdLineEdit->clear();
        usrLineEdit->setFocus();
    }
}


LoginDialog::~LoginDialog(){
    DELETE_PTR(usrLabel);
    DELETE_PTR(usrLineEdit);
    DELETE_PTR(pwdLabel);
    DELETE_PTR(pwdLineEdit);
    DELETE_PTR(loginBtn);
    DELETE_PTR(exitBtn);
    DELETE_PTR(usrLabel);
    DELETE_PTR(usrLabel);
}


