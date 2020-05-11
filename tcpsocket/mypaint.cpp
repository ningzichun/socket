#include "mypaint.h"
#include <QDebug>
#include <QTimer>
#include<QStandardPaths>
MyPaint::MyPaint(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/res/1.png"));
     timer= new QTimer(this);
     PaintFolder=QString(QStandardPaths::writableLocation(QStandardPaths::HomeLocation))+"/tmppaint";
     QString path=PaintFolder;
     // 检查目录是否存在，若不存在则新建
     QDir dir;
     if (!dir.exists(path))
     {
         bool res = dir.mkpath(path);
         qDebug() << "新建画图目录" << res;
     }

     _lpress = false;//初始鼠标左键未按下
     _drawType = 0;//初始为什么都不画
     _drag = 0;//默认非拖拽模式
     _begin = pos();//拖拽的参考坐标，方便计算位移
     _tEdit = new QTextEdit(this);//初始化文本输入框
     _tEdit->hide();//隐藏
     this->setGeometry(350,200,600,400);//设置窗体大小、位置
     setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
     //设置背景黑色
     //方法一
//     QPalette palt(this->palette());
//     palt.setColor(QPalette::Background, Qt::white);
//     this->setAutoFillBackground(true);
//     this->setPalette(palt);
     //方法二
       this->setStyleSheet("background-color:white;");

    //创建工具栏
    QToolBar *tbar = addToolBar(tr("工具栏"));
    tbar->setMovable(false);//工具栏不可移动
    tbar->setIconSize(QSize(16, 16));//设置动作图标的尺寸
    tbar->setStyleSheet("background-color:rgb(199,237,204)");//背景色

    QAction *linesAction = new QAction(tr("&铅笔"), this);//铅笔动作
    linesAction->setIcon(QIcon(":/res/lines.png"));//图标
    linesAction->setShortcut(QKeySequence(tr("Ctrl+P")));//热键
    tbar->addAction(linesAction);//添加到工具栏

    QAction *textAction = new QAction(tr("&文字"), this);//文字动作
    textAction->setIcon(QIcon(":/res/texts.png"));//图标
    textAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(textAction);

    //连接信号与槽函数
    connect(linesAction, SIGNAL(triggered()), this, SLOT(Lines()));
    connect(textAction, SIGNAL(triggered()), this, SLOT(Texts()));
    connect(_tEdit, SIGNAL(textChanged()), this, SLOT(AddTexts()));

}
void MyPaint::solveslot()  //截屏
{
    QScreen *screen=QGuiApplication::primaryScreen();
    QPixmap p=screen->grabWindow(this->winId());
    QString filename = PaintFolder+"/pscr";
    filename+=QString ::number(QDateTime::currentMSecsSinceEpoch()); //毫秒
    filename += ".png";
    qDebug()<<filename;
    if(!p.save(filename,"png"))
    {
        qDebug()<<"不行";
    }
    else
    {
        qDebug()<<"ok";
        emit transportpaint(filename);
    }
    return ;
}
void MyPaint::start()
{
    this->show();

    connect(timer, &QTimer::timeout, this, &MyPaint::solveslot);
    timer->start(1000);

}
void MyPaint::paintEvent(QPaintEvent *)
{
    _pixmap = QPixmap(size());//新建pixmap
    _pixmap.fill(Qt::white);//背景色填充为白色
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    unsigned int i1=0,i5=0;//各种图形的索引

    for(int c = 0;c<_shape.size();++c)//控制用户当前所绘图形总数
    {
        if(_shape.at(c) == 1)//线条
        {
              const QVector<QPoint>& line = _lines.at(i1++);//取出一条线条
              for(int j=0; j<line.size()-1; ++j)//将线条的所有线段描绘出
              {
                  p.drawLine(line.at(j), line.at(j+1));
              }
        }
        else if(_shape.at(c) == 5)//文本
        {
            p.drawText(_tpoint.at(i5),_text.at(i5));
            i5++;
        }
    }
    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0,0, pix);//将pixmap画到窗体
}

void MyPaint::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        if(_drawType == 1)//线条(铅笔)
        {
            _lpress = true;//左键按下标志
            QVector<QPoint> line;//鼠标按下，新的线条开始
            _lines.append(line);//将新线条添加到线条集合
            QVector<QPoint>& lastLine = _lines.last();//拿到新线条
            lastLine.append(e->pos());//记录鼠标的坐标(新线条的开始坐标)
            _shape.append(1);
        }
        else if(_drawType == 5)//文字
        {
            update();//触发窗体重绘
            QPoint p;//鼠标按下，文字开始
            _tpoint.append(p);//将文字坐标添加到文字位置集合
            QPoint& lastp = _tpoint.last();//拿到新文字
            lastp = e->pos();//记录鼠标的坐标
            _tEdit->setGeometry(lastp.x()-6,lastp.y()-17,90,90);//设置文本框的位置、大小

            _tEdit->show();//显示文本输入框
            _text.append("");//添加文本到文本集合
            _tEdit->clear();//因为全局只有一个，所以使用之前要清空
            _shape.append(5);
        }

    }
}

void MyPaint::AddTexts()//当输入框文本改变时调用
{
    QString& last = _text.last();//拿到最后一个文本
    last = _tEdit->toPlainText();//将输入框文本作为文本
}

void MyPaint::mouseMoveEvent(QMouseEvent *e)
{
    if(_lpress)
    {
        if(_drawType == 1)//铅笔画线
        {
            if(_lines.size()<=0) return;//线条集合为空，不画线
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录鼠标的坐标(线条的轨迹)
            update();//触发窗体重绘
        }
    }


}

void MyPaint::mouseReleaseEvent(QMouseEvent *e)
{
    if(_lpress)
    {
        if(_drawType == 1)
        {
            QVector<QPoint>& lastLine = _lines.last();//最后添加的线条，就是最新画的
            lastLine.append(e->pos());//记录线条的结束坐标
            _lpress = false;//标志左键释放
        }
    }
}

void MyPaint::Lines()
{
    _drawType = 1;//铅笔
    _tEdit->hide();//文本框隐藏
}

void MyPaint::Texts()
{
    _drawType = 5;//文字
}
void MyPaint::closeEvent(QCloseEvent* event)  // 关闭窗口事件
{
    timer->stop();
    event->accept();
    emit closepaint(false);
}
void MyPaint::keyPressEvent(QKeyEvent *e) //按键事件
{
     //Ctrl+Z撤销
     if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier)
     {
         if(_shape.size()>0)
         {
             _lines.pop_back();
             _shape.pop_back();
             _drag = 0;//设置为非拖拽模式
             update();
         }
     }

}
