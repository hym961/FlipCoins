#include "selectscene.h"
#include<QPushButton>
#include<QPainter>
#include<QMenubar>
#include "mypushbutton.h"
#include"playscene.h"
#include<QSoundEffect>
SelectScene::SelectScene(QWidget *parent)
    : MyMainWindow{parent}
{
    //返回按钮
    MyPushButton *btnback = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnback->resize(72,32);
    //信号可以链接信号
    connect(btnback,&QPushButton::clicked,this,&SelectScene::backBtnClicked);
    btnback->move(this->width()-btnback->width(),this->height()-btnback->height());
    //创建20个关卡按钮
    const int colwidth = 70;
    const int rowHeight = 70;
    //x y偏移
    const int xOffset=25;
    const int yOffset=130;
    for(int i=0;i<20;i++)
    {
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
        btn->setText(QString::number(i+1));
        //排列
        int row = i/4;
        int col = i%4;
        //行 i/4  列 i%4
        //x坐标=列数*列宽+x偏移
        //y坐标=行数*行高+y偏移
        int x = col*colwidth+xOffset;
        int y = row*rowHeight+yOffset;
        btn->resize(57,57);
        btn->move(x,y);
        connect(btn,&MyPushButton::clicked,[=]()
        {
            //点击关卡按钮后，打开一个新的场景
            PlayScene *playScene = new PlayScene(i+1);
            playScene->setAttribute(Qt::WA_DeleteOnClose);
            playScene->show();
            this->hide();
            //设置playScene关闭的时候自动释放
            connect(playScene,&PlayScene::backBtnClicked,[=]()
            {
                //把第二个场景显示出来，this现在的场景是selectscence
                //因为现在在第二个场景的构造函数下面
                this->show();
                //第三个场景关闭
                playScene->close();
            });
        });

    }
}
//设置背景
void SelectScene::paintEvent(QPaintEvent *event)
{
    //画笔填充按钮
    QPainter painter(this);
    painter.translate(0,this->menuBar()->height());
    QPixmap pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制logo
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,0,pix);

}

