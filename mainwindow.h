#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpServer>
#include<QTcpSocket>

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
    void on_actionGetIP_triggered();

    void on_actionAbout_triggered();

private:
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
