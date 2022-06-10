#pragma once

#include <QGraphicsView>
#include <qtimer.h>
#include <vector>

#include "level.h"
#include "menu.h"
#include "tower.h"
#include "enemy.h"
#include "soldier.h"

class Level;
class Menu;

class Game : public QGraphicsView
{
	Q_OBJECT

public:
	friend void gameConfig(Game* game, int i);
	friend Tower;
	friend Enemy;
	friend Soldier;
	Game(int i,Level* parent);
	//创建远程单位
	bool buildTower(QString s,Tower* tower);
	//创建近战单位
	bool buildSoldier(QString s, Soldier* soldier);
	//设置鼠标样式
	void setMouse(int flag);
	//改变玩家生命值
	void changeLife(int n);
	void keyPressEvent(QKeyEvent* event);
	bool isRemove;
	bool isRally;
private:
	Level* parent;
	Menu* menu;
	int towerNum;
	int soldierNum;
	Tower towerList[15];
	Soldier soldierList[30];
	QTimer enemyTimer;
	QTimer advanceTimer;
	QGraphicsScene* scene;
	int pathNum;
	Soldier* rallyPoint;
	std::vector<std::vector<std::pair<double, double>>> path;
public slots:
	//生成敌人
	void generateEnemy();
};