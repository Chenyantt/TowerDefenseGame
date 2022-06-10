#pragma once

#include <QGraphicsObject>

class Menu;

class Spade : public QGraphicsObject
{
	Q_OBJECT

public:
	Spade();
	//设置父物体
	void setParent(Menu* parent);
	QRectF boundingRect() const;
	//重写绘图事件
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,QWidget* widget);
	//重写鼠标点击函数
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//重写鼠标释放事件
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
	Menu* parent;
};
