#include "level.h"
#include "data.h"

Level::Level(int i, Map* parent) :parent(parent) {
    this->setParent(parent);
    //设置窗口图标
    this->setWindowIcon(QIcon(":/Mainwindow/game_image/icon.png"));
    //设置窗口固定大小
    this->setFixedSize(WIDTH, HEIGHT);
    //设置窗口标题
    this->setWindowTitle("皇城突袭");
    //设置鼠标样式
    setCursor(QCursor(QPixmap(":/Mainwindow/game_image/mouse.png"), 0, 0));
    //创建游戏视图
    this->game = new Game(i, this);
}