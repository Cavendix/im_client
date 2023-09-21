#include "socket.h"
#include "qtcpsocket.h"
#include "qthread.h"
#include<QDebug>
#include<Windows.h>

Socket *Socket::instance()
{
    static Socket* manager=new Socket; // 单例对象
    return manager;
}

Socket::Socket(QObject *parent)
    : QObject(parent)
{
}
void Socket::connectServer()
{
    qDebug() << QThread::currentThread();
    m_tcp= new QTcpSocket(this);
    //创建监听的客户端对象
    qDebug()<<"beginconnect";
    m_tcp->connectToHost("192.168.5.184",8989);
    qDebug()<<"endconnect";

    // 检测服务器是否和客户端断开了连接
    connect(m_tcp, &QTcpSocket::connected, this,[=](){
        qDebug()<<"connect OK";
        emit connectOK();
    });

    connect(m_tcp, &QTcpSocket::disconnected, this, [=]() {
        qDebug()<<"connect error";
        m_tcp->close();
        m_tcp->deleteLater();
        emit connectError();
    });
}

void Socket::signup(QString jsonString)
{
    qDebug() << QThread::currentThread();
    QByteArray bytes = jsonString.toUtf8();
    m_tcp->write(bytes);
    QByteArray code_1 = m_tcp->readAll();
    qDebug()<<"code_1"<<code_1;
    int code = code_1.toInt();
    qDebug()<<"code"<<code;
    emit resultReady(code); // 发射信号，将结果传递出去
}

QString Socket::getAccount()
{
    QByteArray bytes="getacc";
    m_tcp->write(bytes);//发送账号请求
    QByteArray Account_1 = m_tcp->readAll();
    qDebug()<<"Account_1"<<Account_1;
    QString Account = QString::fromUtf8(Account_1);
    qDebug()<<"Account"<<Account;
    return Account;
}

void Socket::createAccount(QString Account, QString Secret)
{
    Account="creacc"+Account;
    Secret="cresec"+Secret;
    QByteArray bytes = Account.toUtf8(); // QString转QByteArray
    m_tcp->write(bytes);//write只接受char和QByteArray
    bytes=Secret.toUtf8();
    m_tcp->write(bytes);
}

void Socket::sendnews(QString)
{

}

