#include "mainwindow.h"

#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QtNetwork>
#include <QFileDialog>
#include "pbutton.h"
#include "dialogabout.h"
#include "dialogip.h"
#include "dialogsettings.h"
#include "dialogclientinfo.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);  // 禁止最大化按钮
    //setFixedSize(this->width(), this->height());  // 禁止拖动窗口大小
    this->setWindowTitle("点到点通信");
    //this->grabKeyboard();
    tcpServer = NULL; //初始化指针
    tcpSocket = NULL;
    acceptedClient = NULL;
    receivingFile = NULL;
    mypaint = new MyPaint;
    pform = new Pform;
    downloadFolder=QString(QStandardPaths::writableLocation(QStandardPaths::HomeLocation))+"/p2pdownload";
    QString path=downloadFolder;
    // 检查目录是否存在，若不存在则新建
    QDir dir;
    if (!dir.exists(path))
    {
        bool res = dir.mkpath(path);
        qDebug() << "新建下载目录" << res;
    }
    /*画图图片临时目录*/
    path=downloadFolder+"/tmp";
    if (!dir.exists(path))
    {
        bool res = dir.mkpath(path);
        qDebug() << "新建临时目录" << res;
    }

    ui->myIP->setText(getHostIpAddress()); //显示网络接口的某一个IP
    ui->logText->insertHtml("按Ctrl+Enter键发送信息<br>请开启监听或连接到其他客户端<br>");

    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);
    /*音频*/
    udpServer = new QUdpSocket(this);
    udpSocket = new QUdpSocket(this);

    connect(udpServer,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));

    /*画图*/
    connect(mypaint,SIGNAL(closepaint(bool)),this,SLOT(changemode()));
    connect(mypaint,SIGNAL(transportpaint(QString)),this,SLOT(changepaintpic(QString)));
//    QAudioFormat format;
//    format.setSampleRate(8000);
//    format.setChannelCount(1);
//    format.setSampleSize(16);
//    format.setCodec("audio/pcm");
//    format.setSampleType(QAudioFormat::SignedInt);
//    format.setByteOrder(QAudioFormat::LittleEndian);
////    output = new QAudioOutput(format,this);
////    outputDevice = output->start();//开始播放

//    input = new QAudioInput(format,this);
//    inputDevice = input->start();//input开始读入输入的音频信号，写入QIODevice，这里是inputDevice
//    connect(inputDevice,SIGNAL(readyRead()),this,SLOT(onReadyRead()));

    /*音频*/

    connect(tcpServer, &QTcpServer::newConnection, [=]() { //接受传入连接
        //取出建立好的套接字
        acceptedClient = tcpServer->nextPendingConnection();
        //获取对方信息
        QString ip = acceptedClient->peerAddress().toString();
        quint16 port = acceptedClient->peerPort();
        QString temp = QString("接收来自 %1:%2 的入站连接").arg(ip).arg(port);
        ui->logText->insertPlainText(temp + "\n");
        ui->connectButton->setText("断开");
//        ui->targetIP->setText(ip.mid(7));
//        ui->targetPort->setText(QString::number(port));
        tcpClient.append(acceptedClient); //加入到客户端列表中

        connect(acceptedClient, &QTcpSocket::readyRead, [=]() { //处理事件：对端有数据传来
            QByteArray array = "";
            for(int i=0;i<tcpClient.length();i++){ //找到触发事件的客户端
                array = tcpClient.at(i)->readAll();
                if(!array.isEmpty()) {
                    readData(tcpClient.at(i),array); //调用readData函数处理数据
                    break;
                }
            }
        });


        connect(acceptedClient, &QTcpSocket::disconnected, [=]() { //连接断开
            for(int i=0;i<tcpClient.length();i++){ //找到触发事件的客户端
                if(tcpClient.at(i)->state()<3){
                    acceptedClient=tcpClient.at(i);
                    tcpClient.removeAt(i);
                    break;
                }
            }
                ui->connectButton->setText("连接");
                QString ip = acceptedClient->peerAddress().toString();
                quint16 port = acceptedClient->peerPort();
                QString temp = QString("丢失与 %1:%2 的连接").arg(ip).arg(port);
                ui->logText->moveCursor(QTextCursor::End);
                ui->logText->insertPlainText(temp + "\n");
            });
    });

    connect(tcpSocket, &QTcpSocket::readyRead, [=]() { //对端有数据传来
        ui->logText->moveCursor(QTextCursor::End); //移动指针
        QByteArray array = tcpSocket->readAll(); //从socket读取数据
        readData(tcpSocket,array); //调用readData函数处理数据
    });

    connect(tcpSocket, &QTcpSocket::disconnected, [=]() { //连接断开
            ui->connectButton->setText("连接");
            QString ip = tcpSocket->peerAddress().toString();
            quint16 port = tcpSocket->peerPort();
            QString temp = QString("断开与 %1:%2 的连接").arg(ip).arg(port);
            ui->logText->moveCursor(QTextCursor::End);
            ui->logText->insertPlainText(temp + "\n");
        });


}
MainWindow::~MainWindow(){
    if (tcpServer->isListening()) {
        output->stop();
        tcpServer->close();
        for(int i=0;i<tcpClient.size();i++){ //与先前连接的客户端断开连接
            tcpClient.at(i)->disconnectFromHost();
        }
        output->stop();
        tcpClient.clear();
        qDebug() << "停止连接";
        ui->startButton->setText("启动监听");
        ui->logText->moveCursor(QTextCursor::End);
        ui->logText->insertPlainText("已停止监听\n");
        return;
    }
    if (tcpSocket->state()>=3) {
        qDebug() << "断开连接";
        QString ip = tcpSocket->peerAddress().toString();
        QString port=QString::number(tcpSocket->peerPort());
        tcpSocket->close();
        ui->connectButton->setText("连接");
        input->stop();
    }
    delete ui;
}


void MainWindow::readyReadSlot(){ //接受
    while(udpServer->hasPendingDatagrams()){
        QHostAddress senderip;
        quint16 senderport;
        qDebug()<<"audio is being received..."<<endl;
        video vp;
        memset(&vp,0,sizeof(vp));
        udpServer->readDatagram((char*)&vp,sizeof(vp),&senderip,&senderport);
        outputDevice->write(vp.data,vp.lens);
    }
}
void MainWindow::onReadyRead() { //发送
    qDebug()<<"It's sending audio!"<<endl;
    video vp;
    memset(&vp,0,sizeof(vp));


    //读取音频
     vp.lens = inputDevice->read(vp.data,1024);//读取音频
     QHostAddress destaddr;
     destaddr.setAddress("192.168.15.228");
     udpSocket->writeDatagram((const char*)&vp,sizeof(vp),udpSocket->peerAddress(),udpSocket->peerPort());
}

QString getDate(){
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("[yyyy.MM.dd hh:mm:ss]");
    return current_date;
}


void MainWindow::readData(QTcpSocket* targetSocket,QByteArray& array){ //读数据函数，传入接收socket
    QString ip = targetSocket->peerAddress().toString(); //获取ip
    quint16 port = targetSocket->peerPort(); //获取端口
    QString temp = getDate();
    temp+=QString("来自 %1:%2 的信息:").arg(ip).arg(port); //输出信息
    ui->logText->moveCursor(QTextCursor::End); //移动指针

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    qDebug()<<"readData"<<current_date;
    QString savelocation;
    while(array.size()>0){
        qDebug()<<array.mid(0,50);
        qDebug()<<array.size();
        qDebug()<<sizeLeft;

        if(array[0]=='F'&&array[1]=='/'){ //文件头
            int current=2;
            QByteArray filename,filesize;
            while(array[current]!='/'){
                filename+=array[current];
                current++;
            }
            current++;
            while(array[current]!='/'){
                filesize+=array[current];
                current++;
            }
            current++;

            sizeLeft=filesize.toLongLong();
            qDebug()<<filesize;
            qDebug()<<sizeLeft;

            savelocation=downloadFolder+'/'+filename;
            if(filename[0]=='p'&&filename[1]=='s'&&filename[2]=='c'&&filename[3]=='r')
                savelocation=downloadFolder+"/tmp/"+filename;
            qDebug()<<savelocation;
            receivingFile=new QFile(savelocation);

            if(receivingFile->open(QIODevice::WriteOnly)){ //覆盖
                ui->logText->append("接收来自 "+ip+" 的文件到 "+receivingFile->fileName()+"\n");
                receivingFile->close();
                array=array.mid(current); //截取子串
                continue;
            }
            else{ //打开失败，停止传输
                ui->logText->append("写文件失败\n");
                delete receivingFile;
                receivingFile=NULL;
            }
            return;
        }
        else if(array[0]=='P'&&array[1]=='/')
        {
            int current=2;
            QString filename="";
            while(array[current]!='/'){
                filename+=array[current];
                current++;
            }
            current++;
            array=array.mid(current);
            ui->logText->append("收到实时手绘，请打开手绘接收器查看。\n");
            ui->logText->moveCursor(QTextCursor::End);

            if(receivingFile!=NULL){ //关闭文件
                receivingFile->close();
                delete receivingFile;
                receivingFile=NULL;
            }
            pform->showpic(downloadFolder+"/tmp/"+filename);
        }
        else if(array[0]=='T'&&array[1]=='/'){ //HTML
            if(array[2]=='/'){ //图片
                int current=3;
                QString filename="";
                while(array[current]!='/'){
                    filename+=array[current];
                    current++;
                }
                current++;
                QString to_append = "<img src=\"";
                to_append+=downloadFolder+'/';
                to_append+=filename;
                to_append+="\"/>\n";
                ui->logText->append(to_append);
                //ui->logText->append(new PBUTTON(downloadFolder+filename,'T'));
                qDebug()<<to_append;
                array=array.mid(current);
                ui->logText->moveCursor(QTextCursor::End);
                return;
            }
            ui->logText->append(temp);
            ui->logText->append(array.mid(2)+"\n");
            ui->logText->moveCursor(QTextCursor::End);
            array="";
            if(receivingFile!=NULL){ //关闭文件
                receivingFile->close();
                delete receivingFile;
                receivingFile=NULL;
            }
        }
        else if(sizeLeft>0){ //文件
            if(array.size()>sizeLeft){ //接收到的数据还有其他部分，这里部分接收
                if(receivingFile->open(QIODevice::Append)){
                    receivingFile->write(array.mid(0,sizeLeft));
                    receivingFile->close();
                    array=array.mid(sizeLeft);
                    sizeLeft=0;
                    ui->logText->append("成功接收了文件\n");
                    continue;
                }
                else{ //写失败
                    delete receivingFile;
                    receivingFile=NULL;
                    break;
                }
            }
            else{
                if(receivingFile->open(QIODevice::Append)){
                    receivingFile->write(array);
                    receivingFile->close();
                    sizeLeft-=array.size();
                    if(sizeLeft==0){
                        ui->logText->append("成功接收了文件\n");
                    }
                    array="";

                }
                else{ //写失败
                    delete receivingFile;
                    receivingFile=NULL;
                    break;
                }
            }
        }
        else{ //文本
            ui->logText->append(array);
            array="";
            ui->logText->moveCursor(QTextCursor::End);
        }
    }
}


void MainWindow::on_startButton_clicked() { //Start Listening
    if (tcpServer->isListening()) {
        output->stop();
        tcpServer->close();
        for(int i=0;i<tcpClient.size();i++){ //与先前连接的客户端断开连接
            tcpClient.at(i)->disconnectFromHost();
        }
        output->stop();
        tcpClient.clear();
        qDebug() << "停止连接";
        ui->startButton->setText("启动监听");
        ui->logText->moveCursor(QTextCursor::End);
        ui->logText->insertPlainText("已停止监听\n");
        return;
    }
    qDebug() << "启动监听";
    ui->logText->moveCursor(QTextCursor::End);
    int theport = ui->listeningPort->text().toInt();
    if (theport >= 65535 || theport < 1) {
        QMessageBox::information(NULL, "提示", "端口号错误，建议端口号 1024-65535 ");
        return;
    }
    if (tcpServer->listen(QHostAddress::Any, theport)) {
        qDebug() << "监听成功";
        ui->startButton->setText("停止监听");
    } else {
        output->stop();
        qDebug() << "监听失败";
        ui->logText->insertPlainText("监听失败\n");
        QMessageBox::information(NULL, "提示", "监听失败，请检查设置");
        return;
    }
    /**/
    quint16 voicePort = ui->listenVoice->text().toInt();
    udpServer->bind(QHostAddress::Any,voicePort);
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    output = new QAudioOutput(format,this);
    outputDevice = output->start();//开始播放
    qDebug() << "开始播放";
    /**/



    ui->logText->insertPlainText("已启动监听，端口号" + ui->listeningPort->text() + "\n");
    ui->logText->insertPlainText("已启动监听，音频端口号" + ui->listenVoice->text() + "\n");

    ui->logText->moveCursor(QTextCursor::End);
}

void MainWindow::on_connectButton_clicked() {
    //获取连接信息
    int theport = ui->targetPort->text().toInt();
    if (theport >= 65535 || theport < 1) {
        QMessageBox::information(NULL, "提示", "端口号错误，建议端口号 1024-65535 ");
        return;
    }
    ui->logText->moveCursor(QTextCursor::End);
    if (tcpSocket->state()>=3) {
        qDebug() << "断开连接";
        QString ip = tcpSocket->peerAddress().toString();
        QString port=QString::number(tcpSocket->peerPort());
        tcpSocket->close();
        ui->connectButton->setText("连接");
        input->stop();
    } else {
        QString targetIP = ui->targetIP->text();
        quint16 targetPort = ui->targetPort->text().toInt();
        quint16 voicePort = ui->targetVoice->text().toInt();
        //连接到服务器
        ui->logText->insertPlainText("正在连接到 " + targetIP + ":"+QString::number(targetPort)+" \n");
        qDebug()<<"连接中";
        ui->logText->moveCursor(QTextCursor::End);
        tcpSocket->connectToHost(QHostAddress(targetIP), targetPort);
        /*音频*/
        udpSocket->connectToHost(QHostAddress(targetIP), voicePort);
        QAudioFormat format;
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleSize(16);
        format.setCodec("audio/pcm");
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        input = new QAudioInput(format,this);
        inputDevice = input->start();//input开始读入输入的音频信号，写入QIODevice，这里是inputDevice
        connect(inputDevice,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
        qDebug() << "开始音频输入";

        /*音频*/
        if(tcpSocket->waitForConnected(3000)){
            ui->connectButton->setText("断开");
            ui->logText->insertPlainText("成功连接到 " + targetIP + ":"+QString::number(targetPort)+" \n");
            ui->logText->insertPlainText("成功连接到 " + targetIP + ":"+QString::number(voicePort)+"（音频端口）\n");
        }
        else{
            input->stop();
            ui->logText->insertPlainText("连接失败\n");
        }
    }
    ui->logText->moveCursor(QTextCursor::End);
}

void MainWindow::on_sendButton_clicked() {
    QString toSend ="T/";
    toSend += ui->inputText->toHtml();
    toSend+="<br>";
    ui->logText->moveCursor(QTextCursor::End);
    bool sent=0;
    for(int i=0;i<tcpClient.size();i++){
        acceptedClient=tcpClient.at(i);
        if (acceptedClient != NULL) {
            if (acceptedClient->state()>=3) {
                sent=1;
                QString ip = acceptedClient->peerAddress().toString();
                QString temp = getDate()+QString("我发送数据到 %1 ").arg(ip);
                acceptedClient->write(toSend.toUtf8().data());
                ui->logText->insertPlainText(temp);
                temp="";

                ui->logText->append(ui->inputText->toHtml()+"\n");
                ui->logText->insertPlainText(temp+='\n');
                ui->logText->insertPlainText(temp+='\n');
                ui->logText->moveCursor(QTextCursor::End);
            }
        }
    }
    if (tcpSocket->state()>=3) {
        sent=1;
        QString ip = tcpSocket->peerAddress().toString();
        QString temp = getDate()+QString("我发送数据到 %1 ").arg(ip);
        tcpSocket->write(toSend.toUtf8().data());
        ui->logText->insertPlainText(temp);
        temp="";

        ui->logText->append(ui->inputText->toHtml()+"\n");
        ui->logText->insertPlainText(temp+='\n');
        ui->logText->insertPlainText(temp);
        ui->logText->moveCursor(QTextCursor::End);
    }
    ui->inputText->clear();
    if(sent){
        ui->selectedFile->setText("发送成功！");
    }
    else{
        ui->logText->insertPlainText("无连接\n");
    }
}



void MainWindow::on_fileButton_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"打开文件");
    if(path.size()<1){
        ui->logText->insertPlainText("请选择有效的文件\n");
        return;
    }
    bool sent=0;
    ui->selectedFile->setText("选择的文件为："+path);
    for(int i=0;i<tcpClient.size();i++){
        acceptedClient=tcpClient.at(i);
        if (acceptedClient != NULL) {
            if (acceptedClient->state()>=3) {
                sent=1;
                sendFile(acceptedClient,path);
            }
        }
    }

    if (tcpSocket->state()>=3) {
        sent=1;
        sendFile(tcpSocket,path);
    }
    if(!sent){
        ui->logText->insertPlainText("无连接\n");
    }
    ui->logText->moveCursor(QTextCursor::End);
}

void MainWindow::sendFile(QTcpSocket *targetSocket, QString &path){
    QFileInfo fileinfo= QFileInfo(path);
    QString filename=fileinfo.fileName();
    qint64 size=fileinfo.size();

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"文件打开失败";
        return;
    }

    QByteArray array="F/"+filename.toUtf8()+"/"+QByteArray::number(size)+"/"; //打上标记区分文字和文件

    int len;
    const int bufsize=1024*16;
    char buf[bufsize]={0};

    ui->logText->moveCursor(QTextCursor::End);
    QString ip = targetSocket->peerAddress().toString();
    QString temp = QString("正在发送文件到 %1 ").arg(ip);
    ui->logText->insertPlainText(temp + "\n");

    targetSocket->write(array);
    if(!targetSocket->waitForBytesWritten(3000)){
        qDebug()<<"超时";
        return;
    }
    do{
        len=file.read(buf,sizeof(buf));
        if(len>0) targetSocket->write(buf,len);
    }while(len>0);

    ui->logText->insertPlainText("发送完成\n");
    file.close();
}

void MainWindow::on_imgButton_clicked() //发送图片
{
    QString path;
    path=QFileDialog::getOpenFileName(this,"打开文件");
    ui->selectedFile->setText("选择的图片为："+path);
    for(int i=0;i<tcpClient.size();i++){
        acceptedClient=tcpClient.at(i);
        if (acceptedClient != NULL) {
            if (acceptedClient->state()>=3) {
                sendFile(acceptedClient,path);
                sendImgTag(acceptedClient,path);
            }
        }
    }

    if (tcpSocket->state()>=3) {
        sendFile(tcpSocket,path);
        sendImgTag(tcpSocket,path);
    }
    ui->logText->moveCursor(QTextCursor::End);

}
void MainWindow::sendPic() //发送图片
{
    QString path;
    path=paintpath;
    qDebug()<<paintpath;

    for(int i=0;i<tcpClient.size();i++){
        acceptedClient=tcpClient.at(i);
        if (acceptedClient != NULL) {
            if (acceptedClient->state()>=3) {
                sendFile(acceptedClient,path);
                sendImgTag(acceptedClient,path);
            }
        }
    }

    if (tcpSocket->state()>=3) {
        sendFile(tcpSocket,path);
        sendImgTag(tcpSocket,path);
    }
    ui->logText->moveCursor(QTextCursor::End);

}
void MainWindow::sendImgTag(QTcpSocket *targetSocket, QString &path){
    QFileInfo fileinfo= QFileInfo(path);
    QString filename=fileinfo.fileName();
    QByteArray to_send="T//";
    if(NowMode==1) to_send="P/";
    to_send+=filename;
    to_send+="/";
    targetSocket->write(to_send);
}

QString MainWindow::getHostIpAddress() { //获取一个本主机的IPv4地址
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i) { //第一次查找，看看有没有公网IPv4地址
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).isGlobal() &&ipAddressesList.at(i).toIPv4Address()) {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (strIpAddress.isEmpty()) {
        for (int i = 0; i < nListSize; ++i) { //第二次查找，看看有没有非网关IPv4地址
            QString temp=ipAddressesList.at(i).toString();
            if (ipAddressesList.at(i) != QHostAddress::LocalHost && temp[temp.size()-2]!='.'&& temp[temp.size()-2]!='1' &&ipAddressesList.at(i).toIPv4Address()) {
                strIpAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
    }
    if (strIpAddress.isEmpty()) {
        for (int i = 0; i < nListSize; ++i) { //第三次查找，返回第一个非回环地址
            QString temp=ipAddressesList.at(i).toString();
            if (ipAddressesList.at(i) != QHostAddress::LocalHost && !ipAddressesList.at(i).isLoopback()) {
                strIpAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
    }
    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty()) strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return strIpAddress;
}

void MainWindow::on_actionGetIP_triggered() {
    DialogIP *IPaddr = new DialogIP(this);
    IPaddr->show();
    IPaddr->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_actionAbout_triggered() {
    DialogAbout *aboutWindow = new DialogAbout(this);
    aboutWindow->show();
    aboutWindow->setAttribute(Qt::WA_DeleteOnClose);
}


void MainWindow::on_actionsettings_triggered()
{
    DialogSettings *settingsWindow = new DialogSettings(this);
    settingsWindow->show();
    settingsWindow->setAttribute(Qt::WA_DeleteOnClose);
}

QString MainWindow::getCilents(){
    QString result="";
    for(int i=0;i<tcpClient.size();i++){
        acceptedClient=tcpClient.at(i);
        if (acceptedClient != NULL) {
            if (acceptedClient->state()>=3) {
                QString ip = acceptedClient->peerAddress().toString();
                quint16 port = acceptedClient->peerPort();
                QString temp = QString("IP：%1  端口：%2\n").arg(ip).arg(port);
                result+=temp;
            }
        }
    }
    if(result.size()<2){
        return "暂无连接";
    }
    return result;
}

QString MainWindow::getServer(){
    if(tcpSocket->state()>=3){
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        QString temp = QString("IP：%1  端口：%2\n").arg(ip).arg(port);
        return temp;
    }
    return "暂无连接";
}

void MainWindow::on_actioninfo_triggered()
{
    DialogClientInfo *clientInfo = new DialogClientInfo(this);
    clientInfo->show();
    clientInfo->setAttribute(Qt::WA_DeleteOnClose);
}
void MainWindow::on_fileopenButton_clicked()
{
    QDesktopServices::openUrl(QUrl("file:"+downloadFolder, QUrl::TolerantMode));
}
void MainWindow::on_paintsendButton_clicked()
{
    mypaint->start();
    NowMode=1;
    //qDebug()<<NowMode<<"\n";
}
void MainWindow::changemode()
{
    NowMode=0;
    //qDebug()<<NowMode<<"\n";
}

void MainWindow::changepaintpic(QString msg)
{
    paintpath=msg;
    sendPic();
    qDebug()<<"发送画图图片"<<"\n";
}
void MainWindow::on_paintreceiveButton_clicked()
{
    pform->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter|| event->key() == Qt::Key_Return)
    {
       on_sendButton_clicked();
       return;
    }

    //QWidget::keyPressEvent(event);
}
