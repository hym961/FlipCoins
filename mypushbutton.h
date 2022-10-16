#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //定义了一个方法叫做MyPushButtonStat,调用该方法就会创建一个枚举类型的变量
    enum MyPushButtonStat
    {
        Normal,
        Pressed
    };
    MyPushButton(QString normalImg,QString pressImg,QWidget *parent = nullptr);
    //往下和往上的动画
    void moveDown();
    void moveUp();
protected:
    void paintEvent(QPaintEvent *ev);
    //设置鼠标事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:
private:
    //正常状态的图片和鼠标按下的图片
    QString mnormalImg;
    QString mpressImg;
    //按钮的状态
    //创建枚举类型的变量，里面存放了Normal和Pressed
    MyPushButtonStat mStat;
public slots:
};

#endif // MYPUSHBUTTON_H
