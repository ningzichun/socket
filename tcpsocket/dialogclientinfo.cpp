#include "dialogclientinfo.h"
#include "ui_dialogclientinfo.h"

DialogClientInfo::DialogClientInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClientInfo)
{
    QPalette bgpal = palette();
    bgpal.setColor (QPalette::Background, QColor (212, 234, 248, 255));
//    bgpal.setColor (QPalette::Background, Qt::transparent);
//    bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255));
        setPalette (bgpal);
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
