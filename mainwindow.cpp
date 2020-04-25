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
    // https://www.bilibili.com/video/BV1yt411d7E4?p=57
    //先测试单线程发文本
    tcpServer=NULL;
    tcpSocket=NULL;
    QVector<QTcpSocket*> currentSockets;

    ui->myIP->setText(getHostIpAddress());
    tcpServer=new QTcpServer(this);
    tcpSocket=new QTcpSocket(this);
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好的套接字
        acceptedClient=tcpServer->nextPendingConnection();
        //获取对方信息
        QString ip=acceptedClient->peerAddress().toString();
        qint16 port=acceptedClient->peerPort();
        QString temp=QString("%1:%2 成功连接").arg(ip).arg(port);
        ui->logText->insertPlainText(temp+"\n");
        connect(acceptedClient,&QTcpSocket::readyRead,[=](){
            QString ip=acceptedClient->peerAddress().toString();
            qint16 port=acceptedClient->peerPort();
            QString temp=QString("%1:%2 :").arg(ip).arg(port);
            ui->logText->append(temp);
           QByteArray array=acceptedClient->readAll();
           ui->logText->append(array);
        });
    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        QString ip=tcpSocket->peerAddress().toString();
        qint16 port=tcpSocket->peerPort();
        QString temp=QString("%1:%2 :").arg(ip).arg(port);
        ui->logText->append(temp);
       QByteArray array=tcpSocket->readAll();
       ui->logText->append(array);
    });
    connect(tcpSocket,&QTcpSocket::connected,[=](){
        qDebug()<<"连接成功";
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    if(tcpServer->isListening()){
        ui->logText->insertPlainText("尝试停止监听\n");
        tcpServer->close();
        qDebug()<<"停止连接";
        ui->logText->insertPlainText("启动监听\n");
    }
    qDebug()<<"启动监听";
    int theport=ui->listeningPort->text().toInt();
    if(theport>=65535 || theport<1) {
        QMessageBox::information(NULL, "提示", "端口号错误，建议端口号 1024-65535 ");
        return;
    }
    if(tcpServer->listen(QHostAddress::Any,theport)){
        qDebug()<<"监听成功";
        ui->startButton->setText("停止监听");
    }
    else{
        qDebug()<<"监听失败";
        ui->logText->insertPlainText("监听失败\n");
        QMessageBox::information(NULL, "提示", "监听失败，请检查设置");
        return;
    }
    ui->logText->insertPlainText("启动监听，端口号"+ui->listeningPort->text()+"\n");
}



void MainWindow::on_connectButton_clicked()
{
    //获取连接信息
    if(tcpSocket->isValid()){
        qDebug()<<"断开连接";
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        ui->logText->insertPlainText("断开到对方的连接\n");
    }
    else{
        QString targetIP=ui->targetIP->text();
        qint16 targetPort=ui->targetPort->text().toInt();
        //连接到服务器
        tcpSocket->connectToHost(QHostAddress(targetIP),targetPort);
    }
}

void MainWindow::on_sendButton_clicked()
{
    QString toSend=ui->inputText->toHtml();
    if(acceptedClient->isValid()){
        acceptedClient->write(toSend.toUtf8().data());
    }
    if(tcpSocket->isValid()){
        tcpSocket->write(toSend.toUtf8().data());
    }

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
