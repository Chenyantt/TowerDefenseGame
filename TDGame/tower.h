#pragma once

#include "character.h"

#include <qgraphicssceneevent.h>
#include <qstring.h>
#include <qmovie.h>

#include "bullet.h"

class Game;

class Tower : public Character
{
	Q_OBJECT

public:
	Tower();
	//设置初始坐标
	void setPos(QPointF point);
	//配置游戏信息
	void setGame(Game* game);
	//设置碰撞检测函数
	QRectF boundingRect() const;
	//重写绘图事件
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//重写鼠标悬停事件
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	//重写鼠标悬停离开事件
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	//重写拖入事件
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	//重写拖离事件
	void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
	//重写悬停释放事件
	void dropEvent(QGraphicsSceneDragDropEvent* event);
	//重写鼠标点击事件
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//重写鼠标释放事件
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	//重写计时器事件
	void timerEvent(QTimerEvent*);
	//重写advance函数
	void advance(int phase);
	//攻击函数
	bool attack();
	enum { Type = UserType + 2 };
	//重写类型函数
	int type() const;
	bool Tower::isEmpty() const;
protected:
	Game* game;
	bool isOccupied;
	bool dragOver;
	QPointF point;
	QString name;
	QMovie* build;
	int buildTimer;
	double attackRadius;
	int attackType;
	int cd;
	Bullet bullet[200];
	int bulletNum;
};