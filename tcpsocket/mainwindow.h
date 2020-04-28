#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

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

   private slots:
    void on_actionGetIP_triggered();

    void on_actionAbout_triggered();

    void on_connectButton_clicked();

    void on_startButton_clicked();

    void on_sendButton_clicked();

    void on_fileButton_clicked();

private:
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    QTcpSocket* acceptedClient;
    int isListening = 0;
    QString downloadFolder;
    Ui::MainWindow* ui;
};
#endif  // MAINWINDOW_H
