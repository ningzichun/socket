#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialogip.h"
#include"dialogabout.h"
#include <QtNetwork>
#include<QPushButton>
#include<QDebug>
#include<QString>
#include<QVector>
#include<QMessageBox>
#include<QAction>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //  QVector<QTcpSocket*> currentSockets;
    /* https://www.bilibili.com/video/BV1yt411d7E4?p=57 先测试单线程发文本 */

    ui->myIP->setText(getHostIpAddress());

    connect(ui->sendButton,&QPushButton::clicked,[=](){
        qDebug()<<"测试";
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionGetIP_triggered()
{
    DialogIP *IPaddr=new DialogIP(this);
    IPaddr->show();
    IPaddr->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout *aboutWindow=new DialogAbout(this);
    aboutWindow->show();
    aboutWindow->setAttribute(Qt::WA_DeleteOnClose);
}


QString MainWindow::getHostIpAddress()
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


void MainWindow::on_connectButton_clicked()
{

}

void MainWindow::on_startButton_clicked()
{
    if(!tcpServer){
        ui->logText->insertPlainText("尝试停止监听\n");
        qDebug()<<"停止连接";

    }
    qDebug()<<"启动监听";
    int theport=ui->listeningPort->text().toInt();
    if(theport>=65535 || theport<1) {
        QMessageBox::information(NULL, "提示", "端口号错误，建议端口号 1024-65535 ");
        return;
    }
    ui->startButton->setText("停止监听");
    tcpServer=new QTcpServer(this);
    if(tcpServer->listen(QHostAddress::Any,theport)){
        qDebug()<<"监听成功";
    }
    else{
        qDebug()<<"监听失败";
        ui->logText->insertPlainText("监听失败\n");
        QMessageBox::information(NULL, "提示", "监听失败，请检查设置");
        return;
    }
    ui->logText->insertPlainText("启动监听，端口号"+ui->listeningPort->text()+"\n");
    qDebug()<<"设立槽函数";
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好的套接字
        tcpSocket=tcpServer->nextPendingConnection();
        //获取对方信息
        QString ip=tcpSocket->peerAddress().toString();
        qint16 port=tcpSocket->peerPort();
        QString temp=QString("[%1:%2]:成功连接").arg(ip).arg(port);
        ui->logText->setText(temp);
    });
}
