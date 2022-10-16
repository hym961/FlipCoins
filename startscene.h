#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include "mymainwindow.h"
#include "selectscene.h"
class StartScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit StartScene(QWidget *parent = nullptr);
private:
    SelectScene mSelectScene;
signals:
public slots:
};

#endif // STARTSCENE_H
