#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include<QPushButton>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sendButton,&QPushButton::clicked,[=](){
        qDebug()<<"测试";
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

