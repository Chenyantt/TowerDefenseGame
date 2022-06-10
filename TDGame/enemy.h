#pragma once

#include <vector>

#include "character.h"

class Game;

class Enemy : public Character
{
	Q_OBJECT

public:
	Enemy(int type, std::vector<std::pair<double, double>> path, Game* game);
	//重写碰撞检测函数
	QRectF boundingRect() const;
	//重写绘图函数
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//重写advance函数
	void advance(int phase);
	//重写类型函数
	enum { Type = UserType + 1 };
	int type() const;
	//判断是否为飞行单位
	bool Enemy::flight() const;
	//攻击函数
	bool attack();
	//重写鼠标点击事件
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//重写鼠标施放事件
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
	Game* game;
	std::vector<std::pair<double, double>> path;
	int name;
	bool warlike;
	bool isFlight;
	bool isDistant;
	int moveSpeed;
	int buff;
	QPointF destination;
	int pathStep;
	int power;
	double attackRadius;
	int frame;
	Character* attackTarget;
	QGraphicsPixmapItem* board;
	QGraphicsSimpleTextItem* text;
};
