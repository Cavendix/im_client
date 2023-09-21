#ifndef SOCKET_H
#define SOCKET_H

#include<QObject>
#include<QTcpServer>
#include<QThread>

class Socket : public QObject
{
    Q_OBJECT
public:
    static Socket* instance();

public slots:

    //连接服务器
    void connectServer();
    //登录
    void signup(QString);
    //从服务器获取随机账号
    QString getAccount();
    //注册
    void createAccount(QString Account, QString Secret);
    //发送信息
    void sendnews(QString);

signals:
    void connectStart();
    void connectOK();
    void connectError();
    void resultReady(int result); // 定义一个信号，用于传递结果
private:
    explicit Socket(QObject *parent = nullptr);

    QTcpSocket*m_tcp;
};

#endif // SOCKET_H
