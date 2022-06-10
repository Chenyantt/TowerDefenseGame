#pragma once

#include <QGraphicsObject>
#include <qpainter.h>
#include <qgraphicssceneevent.h>



class Menu;

class Store : public QGraphicsObject
{
	Q_OBJECT

public:
	Store();
	//�����̵������Ϣ
	void set(QString name,QString image,int cost, Menu* parent);
	//��д��ײ��⺯��
	QRectF boundingRect() const;
	//��д��ͼʱ��
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//��д������¼�
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//��д����ͷ��¼�
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	//��д����ƶ��¼�
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	
private:
	QString name;
	QString image;
	int cost;
	Menu* parent;
};
