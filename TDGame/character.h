#pragma once

#include <QGraphicsObject>



class Character : public QGraphicsObject
{
	Q_OBJECT

public:
	Character();
	//�жϵ�λ�Ƿ�����
	bool isDead();
	//�ı䵥λ����ֵ
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
