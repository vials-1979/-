#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtNetwork/QUdpSocket>
#include<QNetworkInterface>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_rcvdata();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpsocket;
    QString GetlocalIP();
};
#endif // MAINWINDOW_H
