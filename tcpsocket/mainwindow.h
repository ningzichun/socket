#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QtNetwork/QUdpSocket>
#include <QAudio>//一下这五个是QT处理音频的库
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>
#include <mypaint.h>
#include <pform.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QString getHostIpAddress();
    QString getCilents();
    QString getServer();
    QString downloadFolder;
    MyPaint *mypaint;
    Pform *pform;
    qint64 NowMode;  // 图片模式：选择的文件为0 ，画图截图 1
   protected:
    virtual void keyPressEvent(QKeyEvent *ev);
signals:
    void closepaint(bool);
    void transportpaint(QString);
   private slots:
    void on_actionGetIP_triggered();

    void on_actionAbout_triggered();

    void on_connectButton_clicked();

    void on_startButton_clicked();

    void on_sendButton_clicked();

    void on_fileButton_clicked();

    void on_fileopenButton_clicked();

    void on_actionsettings_triggered();

    void on_actioninfo_triggered();

    void on_imgButton_clicked();


    void onReadyRead();
    void readyReadSlot();

    /*画图*/
    void changemode();
    void sendPic();
    void changepaintpic(QString);

    void on_paintsendButton_clicked();

    void on_paintreceiveButton_clicked();

private:
    void readData(QTcpSocket* targetSocket,QByteArray& array);

    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    QTcpSocket* acceptedClient;
    QList<QTcpSocket*> tcpClient;
    int isListening = 0;
    QFile* receivingFile;

    /*音频*/

    QUdpSocket *udpServer;
    QUdpSocket *udpSocket;//用于音频信号的发送

    QAudioInput *input;
    QIODevice *inputDevice;
    QAudioOutput *output;
    QIODevice *outputDevice;


    struct video{
        char data[1024];
        int lens;
    };
    /*音频*/

    void sendFile(QTcpSocket* targetSocket,QString& path);
    void sendImgTag(QTcpSocket* targetSocket,QString& path);
    qint64 sizeLeft=0;
    Ui::MainWindow* ui;

    /*画图*/
    QString paintpath;

};
#endif  // MAINWINDOW_H
