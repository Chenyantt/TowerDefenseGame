#pragma once

#include <QGraphicsObject>

#include "enemy.h"

class Bullet : public QGraphicsObject
{
	Q_OBJECT

public:
	Bullet();
	//��д��ͼ�¼�
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//��д��ײ��⺯��
	QRectF boundingRect() const;
	//�����ӵ���Ϣ
	void setBullet(QString name, Enemy* target,QGraphicsObject* parent);
	//��дadvance����
	void advance(int phase);
	//��д���ͺ���
	enum { Type = UserType + 4 };
	int type() const override;
private:
	QString name;
	Enemy* target;
};
