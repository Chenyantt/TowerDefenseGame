#include "character.h"

#include <qpainter.h>
#include <qpen.h>

Character::Character() :isAttacking(false){
	//����Ѫ����������Χ
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

//��д��ײ��⺯��
QRectF Character::boundingRect() const {
	return QRectF(-54, -39, 108, 78);
}

//��д��ͼ�¼�
void Character::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
	QWidget* widget) {
	Q_UNUSED(option);
	Q_UNUSED(widget);
	//����Ѫ��
	if (healthPoint.first <= 0) {
		healthBar->hide();
	}
	else {
		healthBar->setRect(-20, -39, (qreal)healthPoint.first / healthPoint.second * 40,5);
	}
}

//�жϵ�λ�Ƿ�����
bool Character::isDead() {
	if (healthPoint.first <= 0) {
		return true;
	}
	return false;
}

//�ı䵥λ����ֵ
void Character::changeLife(int n) {
		healthPoint.first += n;
}