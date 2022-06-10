#pragma once

#include <QGraphicsObject>

class Menu;

class Rally : public QGraphicsObject
{
	Q_OBJECT

public:
	Rally();
	//设置父物体
	void setParent(Menu* parent);
	//重写碰撞检测函数
	QRectF boundingRect() const;
	//重写绘图事件
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	//重写鼠标点击事件
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	//重写鼠标释放事件
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
	Menu* parent;
};
