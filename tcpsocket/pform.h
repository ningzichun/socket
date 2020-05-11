#ifndef PFORM_H
#define PFORM_H

#include <QWidget>
#include <QPixmap>
#include <QDebug>
namespace Ui {
class Pform;
}

class Pform : public QWidget
{
    Q_OBJECT

public:
    explicit Pform(QWidget *parent = nullptr);
    ~Pform();
    void showpic(QString);
private:
    Ui::Pform *ui;
};

#endif // PFORM_H
