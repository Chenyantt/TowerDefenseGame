#pragma once

#include <QObject>
#include <qpushbutton.h>

class MyPushButton : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QString normalImage, QString pressedImage = "");
	//重写鼠标点击事件
	void mousePressEvent(QMouseEvent* e);
	//重写鼠标释放事件
	void mouseReleaseEvent(QMouseEvent* e);
private:
	QString normalImage;
	QString pressedImage;
	QString clickedImage;
	
};
