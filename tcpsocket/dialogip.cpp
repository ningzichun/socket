#include "dialogip.h"

#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QtNetwork>

#include "ui_dialogip.h"

QString getAllIpAddress() {
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    strIpAddress += "IP地址列表：\n";
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i) {
        if (ipAddressesList.at(i).toIPv4Address()) {
            strIpAddress += ipAddressesList.at(i).toString() + "\n";
        }
    }
    for (int i = 0; i < nListSize; ++i) {
        if (!ipAddressesList.at(i).toIPv4Address()) {
            if (ipAddressesList.at(i).toString().contains("fe80")) continue;
            strIpAddress += ipAddressesList.at(i).toString() + "\n";
        }
    }

    return strIpAddress;
}

DialogIP::DialogIP(QWidget *parent) : QDialog(parent), ui(new Ui::DialogIP) {
    ui->setupUi(this);
    setWindowTitle("本机IP地址");
    ui->IPtext->setText(getAllIpAddress());
}

DialogIP::~DialogIP() { delete ui; }

void DialogIP::on_exitButton_clicked() { close(); }
