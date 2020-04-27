#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    setWindowTitle("关于");
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_pushButton_clicked()
{
    close();
}
