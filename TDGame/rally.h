#pragma once

#include <QGraphicsObject>

class Menu;

class Rally : public QGraphicsObject
{
	Q_OBJECT

public:
	Rally();
	//���ø�����
	void setParent(Menu* parent);
	//��д��ײ��⺯��
	QRectF boundingRect() const;
	//��д��ͼ�¼�
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	//��д������¼�
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//��д����ͷ��¼�
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
	Menu* parent;
};
