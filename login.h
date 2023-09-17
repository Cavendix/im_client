#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QString>
#include"socket.h"

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
    Socket *worker;
    QString Account;
};

#endif // LOGIN_H
