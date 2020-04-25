#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include<QPushButton>
#include<QDebug>
#include<QString>
#include<QVector>
#include<QMessageBox>

QString getHostIpAddress()
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //  QVector<QTcpSocket*> currentSockets;
    /* https://www.bilibili.com/video/BV1yt411d7E4?p=57 */


    ui->myIP->setText(getHostIpAddress());
    connect(ui->startButton,&QPushButton::clicked,[=](){
        qDebug()<<"启动监听";
        int theport=ui->listeningPort->text().toInt();
        if(theport>=65535 || theport<1) {
            QMessageBox::information(NULL, "提示", "端口号错误，建议端口号 1024-65535 ");
            return;
        }
        ui->startButton->setText("停止监听");
        tcpServer=new QTcpServer(this);
        tcpServer->listen(QHostAddress::Any,theport);
        qDebug()<<"启动监听2";
        connect(tcpServer,&QTcpServer::newConnection,[=](){
            //取出建立好的套接字
            tcpSocket=tcpServer->nextPendingConnection();
            //获取对方信息
            QString ip=tcpSocket->peerAddress().toString();
            qint16 port=tcpSocket->peerPort();
            QString temp=QString("[%1:%2]:成功连接").arg(ip).arg(port);
            ui->logText->setText(temp);
        });
    });



    connect(ui->sendButton,&QPushButton::clicked,[=](){
        qDebug()<<"测试";
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

