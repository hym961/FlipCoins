#include "coinbutton.h"
#include<QPainter>

CoinButton::CoinButton(QWidget *parent)
    : QPushButton{parent}
{
    //初始状态设置
    this->setStat(0);
    //设置按钮不规则的样式，去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");
    //动画定时器信号和槽的实现
    connect(&this->mtimer,&QTimer::timeout,[=]()
    {
        if(this->mStat)
        {
            //银币翻金币
            this->mFrame--;
        }
        else
        {
            //金币翻银币
            //加载相应帧数的图片
             this->mFrame++;

        }
        QString frameName = QString(":/res/Coin000%1.png").arg(this->mFrame);
        this->setIcon(QIcon(frameName));
        //将定时器停掉
        if(this->mFrame==8||this->mFrame==1)
        {
            this->mtimer.stop();
        }
    });
}
//paintEvent在界面创建的时候就会执行一次，之后如果要执行需要调updata和repaint函数
void CoinButton::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BoardNode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //调用父类的paintEvent
    //实际上就是再加载一次图标，覆盖掉背景
    QPushButton::paintEvent(event);
}

void CoinButton::filp()
{
    //翻转，状态置反
    //this->setStat(!this->stat());
    this->setStatWithAnimation(!this->stat());
}
int CoinButton::stat() const
{
    return mStat;
}

void CoinButton::setStat(int newStat)
{
    mStat = newStat;
    if(this->mStat)
    {
        //金币
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else
    {
        //银币
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    //设置icon的大小
    this->setIconSize(this->size());

}

void CoinButton::setStatWithAnimation(int newStat)
{
    this->mStat=newStat;
    if(this->mStat)
    {
        //mStat=1表示的是银币翻金币的过程
        this->mFrame=8;

    }
    else
    {
        //金币翻银币
        //完成金币翻银币的过程，实际上就是利用定时器加载一张一张图片
        this->mFrame = 1;

    }
    this->mtimer.start(30);

}
