#include "storedbutton.h"

StoredButton::StoredButton(QString firstImage, QString secondImage)
	:firstImage(firstImage),secondImage(secondImage),state(true) {
	QPixmap image;
	//����ͼƬ
	image.load(firstImage);
	//���ð�ť��С
	this->setFixedSize(QSize(image.width(), image.height()));
	//���ò�����ť���
	this->setStyleSheet("QPushButton{border:0px;}");
	//���ð�ťͼ��
	this->setIcon(image);
	//���ð�ťͼ���С
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
		//����ͼƬ
		image.load(secondImage);
		state = false;
	}
	else {
		//����ͼƬ
		image.load(firstImage);
		state = true;
		
	}
	//���ð�ť��С
	this->setFixedSize(QSize(image.width(), image.height()));
	//���ò�����ť���
	this->setStyleSheet("QPushButton{border:0px;}");
	//���ð�ťͼ��
	this->setIcon(image);
	//���ð�ťͼ���С
	this->setIconSize(QSize(image.width(), image.height()));
	return QPushButton::mouseReleaseEvent(e);
}