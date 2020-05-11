#ifndef MYPAINT_H
#define MYPAINT_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>
#include  <QDateTime>
#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>
#include <QCloseEvent>
class MyPaint : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyPaint(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void keyPressEvent(QKeyEvent *e); //重写按键事件
    void closeEvent(QCloseEvent* event);
public:
private:
    int _lpress;//左键按下标志
    int _drag;//拖拽标志
    int _drawType;//描绘类型
    QPixmap _pixmap;//画布图片
    QTextEdit *_tEdit;//文本输入框
    QTimer *timer;
    QString PaintFolder;
    QString startTime;
public:
    QVector<QVector<QPoint> > _lines;//线条集合(一条线条可包含多个线段)
    QVector<QRect>  _line;//直线集合
    QVector<QString>  _text;//文字集合
    QVector<QPoint>  _tpoint;//文字位置集合
    QVector<int>  _shape;//图形类型集合，用于撤回功能
    QPoint _begin;//鼠标按下坐标、用于最后一个图形移动

signals:
    void closepaint(bool);
    void transportpaint(QString);
public slots:
    void Lines();
    void Texts();//文字
    void AddTexts();//添加文字
    void solveslot();
    void start();
};
#endif // MYPAINT_H
