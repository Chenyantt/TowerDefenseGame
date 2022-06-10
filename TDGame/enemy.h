#pragma once

#include <vector>

#include "character.h"

class Game;

class Enemy : public Character
{
	Q_OBJECT

public:
	Enemy(int type, std::vector<std::pair<double, double>> path, Game* game);
	//��д��ײ��⺯��
	QRectF boundingRect() const;
	//��д��ͼ����
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//��дadvance����
	void advance(int phase);
	//��д���ͺ���
	enum { Type = UserType + 1 };
	int type() const;
	//�ж��Ƿ�Ϊ���е�λ
	bool Enemy::flight() const;
	//��������
	bool attack();
	//��д������¼�
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//��д���ʩ���¼�
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
