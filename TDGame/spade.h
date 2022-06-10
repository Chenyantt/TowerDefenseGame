#pragma once

#include <QGraphicsObject>

class Menu;

class Spade : public QGraphicsObject
{
	Q_OBJECT

public:
	Spade();
	//���ø�����
	void setParent(Menu* parent);
	QRectF boundingRect() const;
	//��д��ͼ�¼�
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,QWidget* widget);
	//��д���������
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//��д����ͷ��¼�
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
	Menu* parent;
};
