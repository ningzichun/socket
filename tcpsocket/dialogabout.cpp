#include "dialogabout.h"

#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) : QDialog(parent), ui(new Ui::DialogAbout) {
    ui->setupUi(this);
    QPalette bgpal = palette();
    bgpal.setColor (QPalette::Background, QColor (212, 234, 248, 255));
//    bgpal.setColor (QPalette::Background, Qt::transparent);
//    bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255));
        setPalette (bgpal);
    setWindowTitle("关于");
}

DialogAbout::~DialogAbout() { delete ui; }

void DialogAbout::on_pushButton_clicked() { close(); }
