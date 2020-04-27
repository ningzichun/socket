#ifndef DIALOGIP_H
#define DIALOGIP_H

#include <QDialog>

namespace Ui {
class DialogIP;
}

class DialogIP : public QDialog {
    Q_OBJECT

   public:
    explicit DialogIP(QWidget *parent = nullptr);
    ~DialogIP();

   private slots:
    void on_exitButton_clicked();

   private:
    Ui::DialogIP *ui;
};

#endif  // DIALOGIP_H
