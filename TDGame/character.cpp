#include "character.h"

#include <qpainter.h>
#include <qpen.h>

Character::Character() :isAttacking(false){
	//设置血条及攻击范围
	healthBar = new QGraphicsRectItem(this);
	attackRange = new QGraphicsEllipseItem(this);
	QPen pen = attackRange->pen();
	pen.setWidth(3);
	pen.setColor(QColor(255, 255, 255));
	pen.setStyle(Qt::DotLine);
	attackRange->setPen(pen);
	healthBar->setPen(Qt::NoPen);
	attackRange->hide();
}

//重写碰撞检测函数
QRectF Character::boundingRect() const {
	return QRectF(-54, -39, 108, 78);
}

//重写绘图事件
void Character::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
	QWidget* widget) {
	Q_UNUSED(option);
	Q_UNUSED(widget);
	//绘制血条
	if (healthPoint.first <= 0) {
		healthBar->hide();
	}
	else {
		healthBar->setRect(-20, -39, (qreal)healthPoint.first / healthPoint.second * 40,5);
	}
}

//判断单位是否死亡
bool Character::isDead() {
	if (healthPoint.first <= 0) {
		return true;
	}
	return false;
}

//改变单位生命值
void Character::changeLife(int n) {
		healthPoint.first += n;
}