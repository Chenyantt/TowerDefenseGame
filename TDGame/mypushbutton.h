#pragma once

#include <QObject>
#include <qpushbutton.h>

class MyPushButton : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QString normalImage, QString pressedImage = "");
	//��д������¼�
	void mousePressEvent(QMouseEvent* e);
	//��д����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent* e);
private:
	QString normalImage;
	QString pressedImage;
	QString clickedImage;
	
};
