#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include<QFileDialog>
DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    p = (MainWindow*) parent;
    ui->savePath->setText(p->downloadFolder);
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::on_choosePathButton_clicked()
{
    QFileDialog* fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setWindowTitle("选择目录");
    QStringList path;
    if ( fileDialog->exec() == QDialog::Accepted ){
        path = fileDialog->selectedFiles();
        ui->savePath->setText(path.front());
    }
    else return;
}

void DialogSettings::on_buttonBox_accepted()
{
    p->downloadFolder=ui->savePath->text();
}
