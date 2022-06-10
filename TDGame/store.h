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
	//设置商店基本信息
	void set(QString name,QString image,int cost, Menu* parent);
	//重写碰撞检测函数
	QRectF boundingRect() const;
	//重写绘图时间
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget);
	//重写鼠标点击事件
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//重写鼠标释放事件
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	//重写鼠标移动事件
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	
private:
	QString name;
	QString image;
	int cost;
	Menu* parent;
};
