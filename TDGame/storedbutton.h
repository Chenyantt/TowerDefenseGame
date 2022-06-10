#pragma once

#include <QPushButton>

class StoredButton : public QPushButton
{
	Q_OBJECT

public:
	StoredButton(QString firstImage, QString secondImage);
	//��ȡ��ť��ǰ״̬
	bool getState()const ;
	//��д������¼�
	void mousePressEvent(QMouseEvent* e);
	//��д����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent* e);
private:
	bool state;
	QString firstImage;
	QString secondImage;
};
