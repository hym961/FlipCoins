#include "startscene.h"
#include<QPushButton>
#include"mypushbutton.h"
#include<QTimer>
#include<QSoundEffect>
StartScene::StartScene(QWidget *parent)
    : MyMainWindow{parent}
{
    this->setWindowTitle("开始场景");
    MyPushButton *btnStart = new MyPushButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png",this);
    btnStart->resize(144,114);
    //按钮水平居中，垂直方向在3/4位置
    btnStart->move((this->width()-btnStart->width())/2,this->height()*3/4-btnStart->height()/2);
    connect(&this->mSelectScene,&SelectScene::backBtnClicked,[=]()
    {
        //当第二个窗口的返回按钮点击的时候,显示当前窗口
        this->show();
        this->mSelectScene.hide();
        this->move(mSelectScene.pos());
    });
    //开始按钮被点击
    connect(btnStart,&MyPushButton::clicked,[=]()
    {
        QSoundEffect * startSound = new QSoundEffect(this);
        startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
        startSound->play();

        //将按钮设置为不可用
        btnStart->setEnabled(false);
        //播放向下动画
        btnStart->moveDown();
        //往上走的动画会覆盖之前的动画，要等待之前动画播放完再调用
        //定时器
        QTimer::singleShot(150,[=]()
        {
            btnStart->moveUp();
        });
        QTimer::singleShot(300,[=]()
        {
             btnStart->setEnabled(true);
             //场景转换
             //隐藏当前窗口
             this->hide();
             //显示第二个窗口
             this->mSelectScene.show();
             //将窗口移动移动到当前窗口的位置
             this->mSelectScene.move(this->pos());
        });



    });
}
