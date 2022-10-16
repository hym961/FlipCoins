#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <QMainWindow>
#include "mymainwindow.h"
class SelectScene : public MyMainWindow
{
    Q_OBJECT
public:
    //重写构造函数，参数每次传一个关卡的值
    explicit SelectScene(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void backBtnClicked();
public slots:
};

#endif // SELECTSCENE_H
