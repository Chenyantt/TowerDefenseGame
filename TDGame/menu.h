#pragma once

#include <QGraphicsObject>
#include <qmap.h>

#include "game.h"
#include "store.h"
#include "spade.h"
#include "rally.h"

class Game;

class Menu : public QGraphicsObject
{
	Q_OBJECT

public:
	friend void menuConfig(Menu* menu, int i);
	friend Spade;
	friend Rally;
	friend Store;
	friend Game;
	Menu(int i,Game* parent);
	QRectF boundingRect() const;
	//重写绘图事件
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	//获取游戏当前金钱
	int getMoney();
	//改编游戏当前金钱
	void changeMoney(int n);
private:
	Game* parent;
	int life;
	int money;
	std::pair<int, int> boutCount;
	const QMap<QString, int> towerList;
	Store store[7];
	Spade spade;
	Rally rally;
};
