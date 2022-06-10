#include "map.h"

#include "mypushbutton.h"
#include "storedbutton.h"
#include "level.h"
#include "data.h"

Map::Map(QMainWindow*parent)
	: QMainWindow(parent)
{
    //设置窗口图标
    this->setWindowIcon(QIcon(":/Mainwindow/game_image/icon.png"));
    //设置窗口固定大小
    this->setFixedSize(WIDTH, HEIGHT);
    //设置窗口标题
    this->setWindowTitle(TITLE);
    //设置鼠标样式
    setCursor(QCursor(QPixmap(":/Mainwindow/game_image/mouse.png"), 0, 0));

    //创建关卡按钮
    MyPushButton* flags[LEVELNUM];
    for (int i = 0; i < LEVELNUM; ++i) {
        if(LEVELLIST[i]==1) 
            flags[i] = new MyPushButton(":/Mainwindow/game_image/flag1.png", 
                ":/Mainwindow/game_image/flag4.png");
        else 
            flags[i] = new MyPushButton(":/Mainwindow/game_image/flag2.png",
                ":/Mainwindow/game_image/flag3.png");
        flags[i]->setParent(this);
        connect(flags[i], &QPushButton::clicked, [=]() {
            Level* level = new Level(i + 1, this);
            level->show();
            });
    }
    flags[0]->move(130, 45);
    flags[1]->move(300, 120);
    flags[2]->move(250, 220);
    flags[3]->move(400, 330);
    flags[4]->move(540, 300);
    
    //设置提示标语
    MyPushButton* hintBtn = new MyPushButton(":/Mainwindow/game_image/hint.png");
    hintBtn->setParent(this);
    hintBtn->move(350, 180);
    
    //设置返回主菜单按钮
    MyPushButton* backBtn = new MyPushButton(":/Mainwindow/game_image/back1.png",":/Mainwindow/game_image/back2.png");
    backBtn->setParent(this);
    backBtn->move(50, this->height() - 100);
    //关联返回按钮与信号
    connect(backBtn, &QPushButton::clicked, [=]() {
        emit backSignal();
        });
   
    //设置音乐播放按钮
   StoredButton* musicBtn = new StoredButton(":/Mainwindow/game_image/music1.png", ":/Mainwindow/game_image/music2.png");
    musicBtn->setParent(this);
    musicBtn->move(900, 10);
    connect(musicBtn, &QPushButton::clicked, [=]() {
        emit musicSignal(musicBtn->getState());
        });

    //设置百科全书按钮
    MyPushButton* encyclopediaBtn = new MyPushButton(":/Mainwindow/game_image/encyclopedia1.png", ":/Mainwindow/game_image/encyclopedia2.png");
    encyclopediaBtn->setParent(this);
    encyclopediaBtn->move(850, this->height() - 150);
    //设置升级按钮
    MyPushButton* upgradeBtn = new MyPushButton(":/Mainwindow/game_image/upgrade1.png", ":/Mainwindow/game_image/upgrade2.png");
    upgradeBtn->setParent(this);
    upgradeBtn->move(700, this->height() - 150);
    //设置商店按钮
    MyPushButton* shopBtn = new MyPushButton(":/Mainwindow/game_image/shop1.png", ":/Mainwindow/game_image/shop2.png");
    shopBtn->setParent(this);
    shopBtn->move(550, this->height() - 150);
}

void Map::paintEvent(QPaintEvent* e) {
    //设置背景图片
    QPainter painter(this);
    QPixmap image;
    int ret=image.load(":/Mainwindow/game_image/map.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), image);
}