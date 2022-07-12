#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString local_ip;
    local_ip=GetlocalIP();
    qDebug()<<"Local_ip:"<<local_ip;

    udpsocket=new QUdpSocket(this);

    //bind

    udpsocket->bind(QHostAddress::Any,8888);
    connect(udpsocket, SIGNAL(readyRead()), this, SLOT(on_rcvdata()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
*   获取本机IP地址
*/
QString MainWindow::GetlocalIP()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return strIpAddress;
}

void MainWindow::on_pushButton_clicked()
{
    QHostAddress GoalADDr(QString(ui->lineEdit_2->text()));
        quint16 GoalPort = 8888;
        QString sendstr = ui ->lineEdit->text();
        QByteArray str = sendstr.toUtf8();
        udpsocket->writeDatagram(str, GoalADDr, GoalPort);

}


void MainWindow::on_rcvdata(){

    while(udpsocket->hasPendingDatagrams())
        {
            QByteArray Recivedata;
            Recivedata.resize(udpsocket->pendingDatagramSize());
            QHostAddress peerAddr;
            quint16 peerPort;
            udpsocket->readDatagram(Recivedata.data(), Recivedata.size(), &peerAddr, &peerPort);
            QString str = Recivedata.data();
            QString peer = "[From" + peerAddr.toString() + ":" + QString::number(peerPort) +"]";
            ui->textEdit->insertPlainText(peer+str+"\n");

        }
}
