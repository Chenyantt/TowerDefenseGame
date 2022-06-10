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
	//���ó�ʼ����
	void setPosition(QPointF point);
	//������Ϸ������Ϣ
	void setGame(Game* game);
	//��д��ײ��⺯��
	QRectF boundingRect() const;
	//��д��ͼ�¼�
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//��д�����ͣ�¼�
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	//��д����뿪�¼�
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	//��д����뿪�¼�
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	//��д��������¼�
	void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
	//��д��������ͷ��¼�
	void dropEvent(QGraphicsSceneDragDropEvent* event);
	//��дadvance����
	void advance(int phase);
	//��д������¼�
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//��д����ͷ��¼�
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	//��д���ͺ���
	enum { Type = UserType + 3 };
	int type() const;
	//��ȡ��ǰ�赲��λ����
	bool getBlockNum() const;
	//�����赲��λ
	void addBlock(int i);
	//�жϵ�λ�Ƿ�Ϊ��
	bool isEmpty() const;
	//��������
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
