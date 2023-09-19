#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QString>


namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

signals:
    QString getAccount();
    void createAccount(QString,QString);

private slots:
    void on_login_2_clicked();



private:
    Ui::login *ui;
    QString Account;
    int k=0;//判断网络是否连接的标准
};

#endif // LOGIN_H
