#include "mypushbutton.h"
#include<QPushButton>
#include<QPainter>
#include<QPropertyAnimation>
//参数列表，将参数传递给两个对象
MyPushButton::MyPushButton(QString normalImg,QString pressImg,QWidget *parent)
    : QPushButton(parent)
    ,mnormalImg(normalImg)
    ,mpressImg(pressImg)
{
    //初始化状态为Normal
    mStat = Normal;
}

void MyPushButton::moveDown()
{
    //属性动画对象，设置要做动画的对象和属性
    //属性动画就会根据时间生成目标对象某个属性过度的动画
    //这里对象就是按钮this，属性是geometry
    //位置大小属性发生变化
    //给定开始的位置大小属性
    //给定结束的位置大小属性
    //给定时间，给定动画时长
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void MyPushButton::paintEvent(QPaintEvent *ev)
{
    //绘制按钮的图片
    QPainter painter(this);
    QPixmap pix;
    if(mStat==Normal)
    {
        pix.load(mnormalImg);
    }
    if(mStat==Pressed)
    {
        pix.load(mpressImg);
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制按钮的文字
    painter.drawText(0,0,this->width(),this->height(),Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //鼠标按下的时候状态切换到Pressed
    this->mStat=Pressed;
    //项目中需要通过设置来更新界面（即 paintEvent(QPaintEvent *）），这个过程中若是窗口没有发生变化，即使通过调用update()函数来触发重绘函数重绘窗口，也不能立即显示被重绘的窗口。只有窗口变化的时.候才会被显示出来。
    //所以可以通过定时调用 update（）调用绘图事件来实现画面更新
    update();
    //保证信号和槽的功能
    QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->mStat=Normal;
    update();
     QPushButton::mouseReleaseEvent(e);
}

