#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QList>
#include <QtNetwork>
#include<QFileDialog>

void readData(QTcpSocket* targetSocket);


void sendText();


void sendFile();



#endif  // TCPSOCKET_H
