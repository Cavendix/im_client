#include "mainwindow.h"
#include "home.h"
#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>
#include"socket.h"
#include<QDebug>
#include<QThread>

void checkhistory();
void socket() ;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    checkhistory();
    socket();
    return a.exec();
}

void checkhistory()
{
    QFile configFile("config.ini");
    if (!configFile.exists()) {
        qDebug() << "配置文件不存在";
    }
    // 创建一个QSettings对象，指定config.ini文件的路径
    QSettings settings("config.ini", QSettings::IniFormat);

    // 使用value()方法获取已登录账号的值
    QString loggedAccount = settings.value("account").toString();
    qDebug() << "已登录账号: " << loggedAccount;

    // 使用value()方法获取上次登录时间的值
    QString lastLoginTimeString = settings.value("time").toString();

    QDateTime lastLoginTime = QDateTime::fromString(lastLoginTimeString, "yyyy-MM-dd HH:mm:ss");
    qDebug() << "上次登录时间: " << lastLoginTime;

    // 获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
    qDebug() << "当前时间: " << currentTime;
    // 计算时间差
    qint64 secondsDiff = currentTime.secsTo(lastLoginTime);
    qDebug() << secondsDiff;

    // 比对时间差是否小于3天
    if (secondsDiff > -252000) {
        // 执行特定操作
        qDebug() << "时间差小于3天，执行操作";
        home* v=new home;
        v->show();

    } else {
        MainWindow* w=new MainWindow;
        w->show();
        qDebug() << "时间差大于等于3天，不执行操作";
    }
}

void socket() {
    //创建线程对象(不指定父对象，要自己析构)
    QThread* t= new QThread;
    // 获取 Socket单例对象
    Socket* worker = Socket::instance();
    //工作对象移动至子线程
    worker->moveToThread(t);
    //启动子线程
    t->start();

    QObject::connect(worker,&Socket::connectStart,worker,&Socket::connectServer);

    worker->connectStart();

    QObject::connect(worker, &Socket::connectError, [t,worker]() {
        t->quit();//资源释放
        t->wait();
        worker->deleteLater();
        t->deleteLater();
    });
}
