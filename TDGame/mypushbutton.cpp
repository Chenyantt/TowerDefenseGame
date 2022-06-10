#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImage, QString pressedImage)
	:normalImage(normalImage),pressedImage(pressedImage) {
	QPixmap image;
	//加载图片
	image.load(normalImage);
	//设置按钮大小
	this->setFixedSize(QSize(image.width(), image.height()));
	//设置不规则按钮风格
	this->setStyleSheet("QPushButton{border:0px;}");
	//设置按钮图标
	this->setIcon(image);
	//设置按钮图标大小
	this->setIconSize(QSize(image.width(), image.height()));
}

void MyPushButton::mousePressEvent(QMouseEvent* e) {
	if (pressedImage != "") {
		QPixmap image;
		//加载图片
		image.load(pressedImage);
		//设置按钮大小
		this->setFixedSize(QSize(image.width(), image.height()));
		//设置不规则按钮风格
		this->setStyleSheet("QPushButton{border:0px;}");
		//设置按钮图标
		this->setIcon(image);
		//设置按钮图标大小
		this->setIconSize(QSize(image.width(), image.height()));
	}
	return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent* e) {
		QPixmap image;
		//加载图片
		image.load(normalImage);
		//设置按钮大小
		this->setFixedSize(QSize(image.width(), image.height()));
		//设置不规则按钮风格
		this->setStyleSheet("QPushButton{border:0px;}");
		//设置按钮图标
		this->setIcon(image);
		//设置按钮图标大小
		this->setIconSize(QSize(image.width(), image.height()));
		return QPushButton::mouseReleaseEvent(e);
}