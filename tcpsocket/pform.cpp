#include "pform.h"
#include "ui_pform.h"

Pform::Pform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pform)
{
    ui->setupUi(this);
    this->setGeometry(350,100,1200,800);
    this->setWindowTitle("手绘接收窗口");
}

Pform::~Pform()
{
    delete ui;
}

void Pform::showpic(QString path)
{
    QPixmap bgImage(path);
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImage);
    this->setPalette(bgPalette);
    qDebug()<<"收到画图图片啦"+path+"为路径"+"\n";
}
