#include "storedbutton.h"

StoredButton::StoredButton(QString firstImage, QString secondImage)
	:firstImage(firstImage),secondImage(secondImage),state(true) {
	QPixmap image;
	//加载图片
	image.load(firstImage);
	//设置按钮大小
	this->setFixedSize(QSize(image.width(), image.height()));
	//设置不规则按钮风格
	this->setStyleSheet("QPushButton{border:0px;}");
	//设置按钮图标
	this->setIcon(image);
	//设置按钮图标大小
	this->setIconSize(QSize(image.width(), image.height()));
}

bool StoredButton::getState() const {
	return state;
}

void StoredButton::mousePressEvent(QMouseEvent* e) {
	return QPushButton::mousePressEvent(e);
}

void StoredButton::mouseReleaseEvent(QMouseEvent* e) {
	QPixmap image;
	if (state == true) {
		//加载图片
		image.load(secondImage);
		state = false;
	}
	else {
		//加载图片
		image.load(firstImage);
		state = true;
		
	}
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