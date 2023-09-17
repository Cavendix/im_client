#include "socket.h"
#include "qtcpsocket.h"

Socket::Socket(QObject *parent)
    : QObject{parent}
{
    connectServer();
}

void Socket::connectServer()
{
    //创建监听的客户端对象
    m_tcp= new QTcpSocket(this);
    m_tcp->connectToHost(QHostAddress(ip),port);

    // 检测服务器是否和客户端断开了连接
    connect(m_tcp, &QTcpSocket::connected, this, &Socket::connectOK);
    connect(m_tcp, &QTcpSocket::errorOccurred, this, [=](QAbstractSocket::SocketError socketError) {
    });

    connect(m_tcp, &QTcpSocket::disconnected, this, [=]() {
        m_tcp->close();
        m_tcp->deleteLater();
        emit connectError();
    });
    connect(m_tcp, &QTcpSocket::errorOccurred, this, [=](QAbstractSocket::SocketError socketError) {
    });
}

void Socket::sendAccount(QString Account, QString Secret)
{
    Account="senacc"+Account;
    Secret="sensec"+Secret;
    QByteArray bytes = Account.toUtf8(); // QString转QByteArray
    m_tcp->write(bytes);//write只接受char和QByteArray
    bytes=Secret.toUtf8();
    m_tcp->write(bytes);
}

QString Socket::getAccount()
{
    QByteArray Account_1 = m_tcp->readAll();
    QString Account = QString::fromUtf8(Account_1);
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

