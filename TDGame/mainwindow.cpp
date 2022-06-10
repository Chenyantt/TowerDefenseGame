#include "mainwindow.h"

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <qtimer.h>
#include <qpainter.h>

#include "mypushbutton.h"
#include "map.h"
#include "data.h"

Mainwindow::Mainwindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    //设置窗口图标
    this->setWindowIcon(QIcon(":/Mainwindow/game_image/icon.png"));
    //设置窗口固定大小
    this->setFixedSize(WIDTH, HEIGHT);
    //设置鼠标样式
    setCursor(QCursor(QPixmap(":/Mainwindow/game_image/mouse.png"), 0, 0));
    
    //播放背景音乐
    QMediaPlaylist* playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/Mainwindow/game_music/gamebgsound.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer* music = new QMediaPlayer(this);
    music->setPlaylist(playlist);
    music->play();

    //创建开始按钮
    MyPushButton* startBtn = new MyPushButton(":/Mainwindow/game_image/play_btn1.png", ":/Mainwindow/game_image/play_btn2.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5-startBtn->width() * 0.5, this->height() * 0.65);
    
    Map* m = new Map(this);
    //关联开始按钮与下一场景
    connect(startBtn, &QPushButton::clicked, [=]() {
        QTimer::singleShot(100, this, [=]() {
            this->hide();
            m->show();
            });
        });
    //创建背景音乐开关按钮
    connect(m, &Map::musicSignal, [=](bool state) {
        if (state == true) music->play();
        else music->stop();
        });
    //关联下一场景的返回主菜单图标
    connect(m, &Map::backSignal, [=]() {
        this->show();
        m->hide();
        QTimer::singleShot(100, this, [=]() {
            this->show();
            m->hide();
            });
        });
}

void Mainwindow::paintEvent(QPaintEvent* e) {
    //设置背景图片
    QPainter painter(this);
    QPixmap image;
    image.load(":/Mainwindow/game_image/background1.jpg");
    painter.drawPixmap(0, 0, this->width(),this->height(),image);
    image.load(":/Mainwindow/game_image/background2.png");
    painter.drawPixmap(310, 60, 450,350,image);
}