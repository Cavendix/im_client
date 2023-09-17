#include "login.h"
#include "ui_login.h"
#include<QMessageBox>


login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //创建任务对象
    worker= new Socket;
    //获取账号
    connect(this,&login::getAccount,worker,&Socket::getAccount);
    Account =emit getAccount();
    ui->lineEdit->setText(Account);
    ui->lineEdit->setReadOnly(true);

    connect(this,&::login::getAccount,worker,&Socket::createAccount);

}

login::~login()
{
    delete ui;
}


void login::on_login_2_clicked()
{
    QString pass=ui->lineEdit_2->text();
    QString pass_=ui->lineEdit_3->text();

    if(pass==""){
        QMessageBox::StandardButton btn_3=QMessageBox::warning(this,"warning","密码太简单",QMessageBox::Yes);
    }
    else if(pass!=pass_){
        QMessageBox::StandardButton btn_2=QMessageBox::warning(this,"warning","两次密码不同",QMessageBox::Yes);
    }
    else{
        emit createAccount(Account,pass);
        QMessageBox::StandardButton btn_4=QMessageBox::information(this,"information","注册成功",QMessageBox::Yes);
    }
}

