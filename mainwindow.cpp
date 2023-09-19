#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"socket.h"
#include"login.h"
#include<QThread>
#include<QMessageBox>
#include"home.h"
#include<windows.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("欢迎使用");

    //状态栏的动作,显示网络是否连接
    QLabel*m_status=new QLabel;
    ui->statusbar->addWidget(new QLabel("网络状态:"));
    m_status->setPixmap(QPixmap(":/picture/F.png").scaled(20,20));
    ui->statusbar->addWidget(m_status);

    //创建线程对象(不指定父对象，要自己析构)
    QThread* t= new QThread;

    t->start();//启动子线程

    //创建任务对象
    Socket *worker= new Socket;

    //工作对象移动至子线程
    worker->moveToThread(t);

    connect(this,&MainWindow::sendAccount,worker,&Socket::sendAccount);
    connect(this,&MainWindow::startConnect,worker,&Socket::connectServer);
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

    connect(worker,&Socket::resultReady, [this](int result) {
        qDebug() << "Result received in main:" << result;
        i=result;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signup_2_clicked()//登录按钮
{

    QString account=ui->account_2->text();
    QString secret=ui->secret_2->text();
    if(account.isEmpty()){
        QMessageBox::warning(this,"登录","账号不能为空");
        return;
    }
    else if(secret.isEmpty()){
        QMessageBox::warning(this,"登录","密码不能为空");
        return;
    }
    else if(k==0){
        QMessageBox::warning(this,"登录","服务器未连接");
        emit startConnect();
    }
    else{
        emit sendAccount(account,secret);
        qDebug()<<i;
        if(i==2)QMessageBox::warning(this,"登录","查无此账号");
        else if(i==0)QMessageBox::warning(this,"登录","密码错误");
        else {
            home* v=new home;
            v->show();
            this->close();
        }
    }
}


void MainWindow::on_login_2_clicked()
{
    if(k==0){
    QMessageBox::warning(this,"登录","服务器未连接");
    emit startConnect();
    }
    else{
        login* point=new login;
        point->show();
    }
}



