#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include<QThread>
#include"socket.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //创建任务对象
    setWindowTitle("欢迎使用");

    //状态栏的动作,显示网络是否连接
    QLabel*m_status=new QLabel;
    ui->statusbar->addWidget(new QLabel("网络状态:"));
    m_status->setPixmap(QPixmap(":/picture/F.png").scaled(20,20));
    ui->statusbar->addWidget(m_status);

    //创建线程对象(不指定父对象，要自己析构)
    QThread* t= new QThread;
    //创建任务对象
    Socket *worker= new Socket;
    //处理子线程发送的信号
    connect(worker,&Socket::connectOK,this,[=](){
        m_status->setPixmap(QPixmap(":/picture/T.png").scaled(20, 20));
        k=1;

    });
    connect(worker, &Socket::connectError, this, [=]() {
        t->quit();//资源释放
        t->wait();
        worker->deleteLater();
        t->deleteLater();

        m_status->setPixmap(QPixmap(":/picture/F.png").scaled(20, 20));
        k=0;
        //ui->login_2->setEnabled(true);
    });

    //获取账号
    connect(this,&login::getAccount,worker,&Socket::getAccount);
    Account=emit getAccount();
    ui->lineEdit->setText(Account);
    ui->lineEdit->setReadOnly(true);

    connect(this,&::login::createAccount,worker,&Socket::createAccount);



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
        this->close();
    }

}

