#include "mainwindow.h"
#include "home.h"
#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>


void checkhistory();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    checkhistory();
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
                QString lastLoginTime = settings.value("time").toString();
    qDebug() << "上次登录时间: " << lastLoginTime;

                // 获取当前时间
                QDateTime currentTime = QDateTime::currentDateTime();

    // 指定目标时间（2023:9:19:11:05:00）
    QDateTime targetTime(QDate(2023, 9, 19), QTime(11, 5, 0));

    // 计算时间差
    qint64 secondsDiff = currentTime.secsTo(targetTime);
    qint64 daysDiff = secondsDiff / 86400; // 一天有86400秒

    // 比对时间差是否小于3天
    if (daysDiff < 3) {
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
