#pragma once

#include <QGraphicsItem>
#include "character.h"

#include "tower.h"

class Game;

class Soldier : public Character
{
	Q_OBJECT

public:
	friend Tower;
	Soldier();
	//设置初始坐标
	void setPosition(QPointF point);
	//设置游戏配置信息
	void setGame(Game* game);
	//重写碰撞检测函数
	QRectF boundingRect() const;
	//重写绘图事件
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//重写鼠标悬停事件
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	//重写鼠标离开事件
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	//重写鼠标离开事件
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	//重写鼠标拖离事件
	void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
	//重写鼠标拖入释放事件
	void dropEvent(QGraphicsSceneDragDropEvent* event);
	//重写advance函数
	void advance(int phase);
	//重写鼠标点击事件
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//重写鼠标释放事件
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	//重写类型函数
	enum { Type = UserType + 3 };
	int type() const;
	//获取当前阻挡单位数量
	bool getBlockNum() const;
	//增加阻挡单位
	void addBlock(int i);
	//判断单位是否为空
	bool isEmpty() const;
	//攻击函数
	void attack();
private:
	Game* game;
	bool isOccupied;
	bool dragOver;
	QPointF point;
	QString name;
	double attackRadius;
	int attackAbility;
	int attackType;
	std::pair<int,int> blockNum;
	int frame;
	Character* attackTarget;
};
