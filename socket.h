#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include<QTcpServer>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

    //连接服务器
    void connectServer();
    //登录
    void sendAccount(QString ,QString);
    //从服务器获取随机账号
    QString getAccount();
    //注册
    void createAccount(QString Account, QString Secret);

signals:
    void connectOK();
    void connectError();
private:
    QTcpSocket*m_tcp;
    unsigned short port=8989;
    QString ip="192.168.5.184";
};

#endif // SOCKET_H
