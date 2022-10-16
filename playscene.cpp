#include "playscene.h"
#include "mypushbutton.h"
#include<QPainter>
#include<QMenubar>
#include<QLabel>
#include "coinbutton.h"
#include "dataconfig.h"
#include <QMap>
#include <QLabel>
#include<QMessageBox>
#include<QPropertyAnimation>
#include<QSoundEffect>
//遇到Debug类的错误，修改过后需要重新构建项目
//修改父类，主要原因是可以复用窗口的属性和方法以及构造函数
PlayScene::PlayScene(int level,QWidget *parent)
    : MyMainWindow{parent}
{
    mHasWin=false;
    MyPushButton *btnback = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnback->resize(72,32);
    //信号可以链接信号
    connect(btnback,&QPushButton::clicked,this,&PlayScene::backBtnClicked);
    btnback->move(this->width()-btnback->width(),this->height()-btnback->height());
    //添加左下角的label
    QLabel *label = new QLabel(this);
    label->setText(QString("level : %1").arg(level));
    label->resize(150,50);
    //设置字体
    label->setFont(QFont("华文新魏",20));
    //移动到左下角
    label->move(30,this->height()-label->height());
    const int colwidth = 50;
    const int rowHeight = 50;
    const int xOffset=57;
    const int yOffset=200;
    //取出第几关的二维数组
    dataConfig data;
    QVector<QVector<int>> dataArray = data.mData[level];
    //16个硬币按钮
    for(int row=0;row<4;++row)
    {
        for(int col=0;col<4;++col)
        {
            //存储按钮到数组第几行第几列
            CoinButton *btn = new CoinButton(this);
            mCoins[row][col] = btn;
            int x = col*colwidth+xOffset;
            int y = row*rowHeight+yOffset;
            btn->setGeometry(x,y,50,50);
            //设置第几行第几列的置，从dataConfig的数据中获取
            btn->setStat(dataArray[row][col]);
            connect(btn,&CoinButton::clicked,[=]()
            {
                //每次点击硬币的时候就改变状态，状态置反
                //btn->filp();
                //
                this->flip(row,col);
            });
        }
    }

}

void PlayScene::flip(int row, int col)
{
    //如果胜利了，就直接返回
    if(mHasWin)
    {
        return ;
    }
    this->mCoins[row][col]->filp();
    QSoundEffect * startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    startSound->play();
    //翻动第一个硬币之后，延时翻动周围的硬币
    QTimer::singleShot(250,[=]()
    {
        //翻动上下左右的硬币
        //下一行的硬币
        if(row+1<4)
        {
            this->mCoins[row+1][col]->filp();
        }
        if(row-1>=0)
        {
            //上一行的硬币
            this->mCoins[row-1][col]->filp();
        }
        if(col-1>=0)
        {
            //左边的硬币
            this->mCoins[row][col-1]->filp();
        }
        if(col+1<4)
        {
            //右边的硬币
            this->mCoins[row][col+1]->filp();
        }
        //判断游戏是否胜利
        this->judgeWin();
    });


}

void PlayScene::judgeWin()
{
    //16个硬币按钮判断状态都是1
    for(int row=0;row<4;++row)
    {
        for(int col=0;col<4;++col)
        {
            //判断某个硬币是银币,游戏就得继续
            //只要有一个银币，游戏就返回继续
            if(!this->mCoins[row][col]->stat())
            {
                return ;
            }
        }
    }
    //所有都是金币的情况下，游戏结束
    //QMessageBox::information(this,"恭喜","你已经胜利了");
    mHasWin=true;
    QSoundEffect * startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    startSound->play();
    //播放胜利动画
    QLabel * labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();
    labelWin->move((this->width()-labelWin->width())/2,-labelWin->height());
    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));
    animation->setDuration(1000);
    //设置动画的运动区间
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //动画播放完毕自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void PlayScene::paintEvent(QPaintEvent *event)
{
    //画背景
    //画笔填充按钮
    QPainter painter(this);
    painter.translate(0,this->menuBar()->height());
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制logo
    pix.load(":/res/Title.png");
    //缩小Logo
    pix = pix.scaled(pix.width()/2,pix.height()/2);
    painter.drawPixmap(0,0,pix);
}
