#pragma once

#include <QGraphicsObject>

#include "enemy.h"

class Bullet : public QGraphicsObject
{
	Q_OBJECT

public:
	Bullet();
	//重写绘图事件
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//重写碰撞检测函数
	QRectF boundingRect() const;
	//设置子弹信息
	void setBullet(QString name, Enemy* target,QGraphicsObject* parent);
	//重写advance函数
	void advance(int phase);
	//重写类型函数
	enum { Type = UserType + 4 };
	int type() const override;
private:
	QString name;
	Enemy* target;
};
