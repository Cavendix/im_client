#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"socket.h"
#include"login.h"
#include<QMessageBox>
#include"home.h"
#include<windows.h>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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
    k=0;
    // 获取 Socket单例对象
    Socket* worker = Socket::instance();

    //处理子线程发送的信号
    QObject::connect(worker,&Socket::connectOK,this,[=](){
        m_status->setPixmap(QPixmap(":/picture/T.png").scaled(20, 20));
        k=1;

    });
    QObject::connect(worker, &Socket::connectError, this, [=]() {
        worker->deleteLater();
        m_status->setPixmap(QPixmap(":/picture/F.png").scaled(20, 20));
        k=0;
    });

    QObject::connect(this,&MainWindow::signup,worker,&Socket::signup);
    QObject::connect(this,&MainWindow::startConnect,worker,&Socket::connectServer);

    QObject::connect(worker,&Socket::resultReady, [this](int result) {
        qDebug() << "Result received in main:" << result;
        i=result;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString json(QString account,QString secret){
    // 创建一个JSON数组
    QJsonArray jsonArray;

    // 创建一个JSON对象，包含 "signup"、Account 和 Secret
    QJsonObject jsonObject;
    jsonObject["action"] = "signup";
    jsonObject["Account"] = account; // 替换为实际的账号值
    jsonObject["Secret"] = secret;   // 替换为实际的密钥值

    // 将JSON对象添加到数组中
    jsonArray.append(jsonObject);

    // 创建一个JSON文档并将数组转换为字符串
    QJsonDocument jsonDoc(jsonArray);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    qDebug() << "JSON字符串:" << jsonString;
    return jsonString;
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
        QString jsonString=json(account,secret);
        emit signup(jsonString);
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



