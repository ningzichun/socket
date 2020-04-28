#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = nullptr);
    ~DialogSettings();

private slots:
    void on_choosePathButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogSettings *ui;
    MainWindow * p;
};

#endif // DIALOGSETTINGS_H
