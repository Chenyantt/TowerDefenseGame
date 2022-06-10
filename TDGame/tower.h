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
	//���ó�ʼ����
	void setPos(QPointF point);
	//������Ϸ��Ϣ
	void setGame(Game* game);
	//������ײ��⺯��
	QRectF boundingRect() const;
	//��д��ͼ�¼�
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//��д�����ͣ�¼�
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	//��д�����ͣ�뿪�¼�
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	//��д�����¼�
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	//��д�����¼�
	void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
	//��д��ͣ�ͷ��¼�
	void dropEvent(QGraphicsSceneDragDropEvent* event);
	//��д������¼�
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//��д����ͷ��¼�
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	//��д��ʱ���¼�
	void timerEvent(QTimerEvent*);
	//��дadvance����
	void advance(int phase);
	//��������
	bool attack();
	enum { Type = UserType + 2 };
	//��д���ͺ���
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