#pragma once

#include <QGraphicsObject>



class Character : public QGraphicsObject
{
	Q_OBJECT

public:
	Character();
	//判断单位是否死亡
	bool isDead();
	//改变单位生命值
	void changeLife(int n);
protected:
	std::pair<int,int> healthPoint;
	int attackAbility;
	bool isAttacking;
	QString image;
	QGraphicsEllipseItem* attackRange;
	 QGraphicsRectItem* healthBar;
	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
};
