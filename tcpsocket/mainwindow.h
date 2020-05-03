#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

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

   private slots:
    void on_actionGetIP_triggered();

    void on_actionAbout_triggered();

    void on_connectButton_clicked();

    void on_startButton_clicked();

    void on_sendButton_clicked();

    void on_fileButton_clicked();

    void on_actionsettings_triggered();

    void on_actioninfo_triggered();

    void on_imgButton_clicked();

private:
    void readData(QTcpSocket* targetSocket,QByteArray& array);

    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    QTcpSocket* acceptedClient;
    QList<QTcpSocket*> tcpClient;
    int isListening = 0;
    QFile* receivingFile;

    void sendFile(QTcpSocket* targetSocket,QString& path);
    void sendImgTag(QTcpSocket* targetSocket,QString& path);
    qint64 sizeLeft=0;
    Ui::MainWindow* ui;
};
#endif  // MAINWINDOW_H
