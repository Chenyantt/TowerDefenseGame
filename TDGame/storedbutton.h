#pragma once

#include <QPushButton>

class StoredButton : public QPushButton
{
	Q_OBJECT

public:
	StoredButton(QString firstImage, QString secondImage);
	//获取按钮当前状态
	bool getState()const ;
	//重写鼠标点击事件
	void mousePressEvent(QMouseEvent* e);
	//重写鼠标释放事件
	void mouseReleaseEvent(QMouseEvent* e);
private:
	bool state;
	QString firstImage;
	QString secondImage;
};
