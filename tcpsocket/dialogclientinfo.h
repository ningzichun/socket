#ifndef DIALOGCLIENTINFO_H
#define DIALOGCLIENTINFO_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogClientInfo;
}

class DialogClientInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogClientInfo(QWidget *parent = nullptr);
    ~DialogClientInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogClientInfo *ui;
    MainWindow * p;
};

#endif // DIALOGCLIENTINFO_H
