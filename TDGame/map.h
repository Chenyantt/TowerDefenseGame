#pragma once

#include <QMainWindow>

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(QMainWindow *parent);
	void paintEvent(QPaintEvent* e);
signals:
	void backSignal();
	void musicSignal(bool state);
};
