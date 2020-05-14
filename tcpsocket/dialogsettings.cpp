#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include<QFileDialog>
DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    QPalette bgpal = palette();
    bgpal.setColor (QPalette::Background, QColor (212, 234, 248, 255));
//    bgpal.setColor (QPalette::Background, Qt::transparent);
//    bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255));
        setPalette (bgpal);
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
