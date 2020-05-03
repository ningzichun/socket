#include "dialogclientinfo.h"
#include "ui_dialogclientinfo.h"

DialogClientInfo::DialogClientInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClientInfo)
{
    ui->setupUi(this);
    p = (MainWindow*) parent;

    ui->text1->setText(p->getCilents());
    ui->text2->setText(p->getServer());
}

DialogClientInfo::~DialogClientInfo()
{
    delete ui;
}

void DialogClientInfo::on_pushButton_clicked()
{
    close();
}
