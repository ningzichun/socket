#ifndef PBUTTON_H
#define PBUTTON_H

#include <QDialog>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QKeyEvent>
namespace Ui {
class PBUTTON;
}

class PBUTTON : public QPushButton {
    Q_OBJECT

   public:
    explicit PBUTTON(QWidget *parent = nullptr);
    PBUTTON(QString filename,char type)
    {
        this->filename=filename;
        if(type=='T') this->setText("查看图片");
        else this->setText("查看文件");
        connect(this,SIGNAL(clicked(bool)),this,SLOT(displaySlot()));
    }

    QString filename;
    //~PBUTTON();

   private slots:
   void displaySlot()
   {
        #ifdef Q_OS_WIN32   // win 下用默认程序打开
        bool is_open = QDesktopServices::openUrl(QUrl(filename, QUrl::TolerantMode));
        if(!is_open)
        {
            qDebug()<<"open file failed";
            return;
        }
        #else
            QString  cmd= QString("xdg-open ")+ filename;　　　//在linux下，可以通过system来xdg-open命令调用默认程序打开文件；
            system(cmd.toStdString().c_str());
        #endif
   }

   private:
    Ui::PBUTTON *ui;
};
#endif  // PBUTTON
