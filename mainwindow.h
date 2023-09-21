#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void signup(QString);//发送账号密码给子线程的信号

    void startConnect();//发送ip端口给子线程的信号

private slots:
    void on_signup_2_clicked();

    void on_login_2_clicked();

private:
    Ui::MainWindow *ui;
    int i;
    int k;
};
#endif // MAINWINDOW_H
