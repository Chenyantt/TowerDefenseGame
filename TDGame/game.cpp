#include "game.h"

#include "data.h"
#include "menu.h"
#include "config.h"

#include <qkeyevent>


Game::Game(int i, Level* parent):parent(parent),isRemove(false),isRally(false),rallyPoint(NULL){
	this->setParent(parent);
	//设置游戏视图大小
	this->setGeometry(0, 0, WIDTH, HEIGHT);
	setFixedSize(WIDTH, HEIGHT);
	//设置游戏场景
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, WIDTH, HEIGHT);
	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	this->setRenderHint(QPainter::Antialiasing);
	//设置背景图片展示方式
	this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	//设置背景图片
	QPixmap pixmap(QString(":/Mainwindow/game_image/level%1.jpg").arg(QString::number(i)));
	pixmap = pixmap.scaled(WIDTH, HEIGHT);
	this->setBackgroundBrush(pixmap);
	menu = new Menu(i, this);
	scene->addItem(menu);
	menu->setPos(815, 0);
	//添加配置文件
	gameConfig(this, i);
	//添加物体至场景中
	for (int i = 0; i < towerNum; ++i) {
		scene->addItem(&towerList[i]);
		towerList[i].setGame(this);
		towerList[i].setParent(scene);
	}
	for (int i = 0; i < soldierNum; ++i) {
		scene->addItem(&soldierList[i]);
		soldierList[i].setGame(this);
		soldierList[i].setParent(scene);
	}
	//设置游戏帧计时器
	connect(&advanceTimer, SIGNAL(timeout()), scene, SLOT(advance()));
	advanceTimer.start(100);
	//设置敌人生成计时器
	connect(&enemyTimer, SIGNAL(timeout()), SLOT(generateEnemy()));
	enemyTimer.start(7500);
};

//修建远程单位
bool Game::buildTower(QString s, Tower* tower) {
	if (menu->money >= TOWERLIST[s]) {
		menu->money -= TOWERLIST[s];
		menu->update();
		return true;
	}
	return false;
}

//修建近战单位
bool Game::buildSoldier(QString s, Soldier* soldier) {
	if (menu->money >= SOLDIERLIST[s]) {
		menu->money -= SOLDIERLIST[s];
		menu->update();
		return true;
	}
	return false;
}

//设置鼠标样式
void Game::setMouse(int flag) {
	if (flag==1) {
		this->parent->setCursor(QCursor(QPixmap(":/Mainwindow/game_image/spade1.png"), 0, 0));
	}
	else if (flag == 2) {
		this->parent->setCursor(QCursor(QPixmap(":/Mainwindow/game_image/rally.png"), 0, 0));
	}
	else {
		this->parent->setCursor(QCursor(QPixmap(":/Mainwindow/game_image/mouse.png"), 0, 0));
	}
}

//产生敌人
void Game::generateEnemy() {
	srand(time(NULL));
	if (this->menu->boutCount.first == this->menu->boutCount.second) {
		enemyTimer.stop();
	}
	else {
		int tmp = rand() % 6;
		Enemy* e=new Enemy(tmp+1,path[tmp%2],this);
		scene->addItem(e);
		this->menu->boutCount.first++;
		this->menu->update();
	}
}

//改变玩家生命值
void Game::changeLife(int n) {
	menu->life += n;
	menu->update();
}

void Game::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_P:
		if (advanceTimer.isActive()) {
			advanceTimer.stop();
			enemyTimer.stop();
			menu->setEnabled(false);
			scene->advance();
		}
		else {
			menu->setEnabled(true);
			advanceTimer.start();
			enemyTimer.start();
		}
	break;
	default:
		event->ignore();
		break;
	}
}