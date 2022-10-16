#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include<QTimer>
class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);
    void filp();
    int stat() const;
    void setStat(int newStat);
    //setStat带动画的函数
    void setStatWithAnimation(int newStat);
protected:
    //设置背景图片
    void paintEvent(QPaintEvent *event);

signals:
private slots:
private:
    //硬币状态，0代表银币，1代表金币
    int mStat;
    //要记录动画的当前帧
    int mFrame;
    //定时器
    QTimer mtimer;
};

#endif // COINBUTTON_H
