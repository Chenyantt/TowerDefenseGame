#include "config.h"

#include <qfile.h>

//菜单配置函数
void menuConfig(Menu* menu, int i) {
	QFile file(QString("./level%1.txt").arg(QString::number(i)));
	file.open(QIODevice::ReadOnly);
	//初始化金钱、生命值、怪物波数
	menu->life = file.readLine().toInt();
	menu->money= file.readLine().toInt();
	menu->boutCount.second= file.readLine().toInt();
	menu->boutCount.first = 0;
	file.close();
}

//游戏配置函数
void gameConfig(Game* game, int i) {
	QFile file(QString("./level%1.txt").arg(QString::number(i)));
	file.open(QIODevice::ReadOnly);
	for (int i = 0; i < 3; ++i) {
		file.readLine();
	}
	//初始化远程单位列表
	game->towerNum= file.readLine().toInt();
	QStringList l = QString(file.readLine()).split('+');
	for (int i = 0; i < game->towerNum; i++) {
		double a, b;
		splitPair(l[i], &a, &b);
		game->towerList[i].setPos(QPoint(a,b));
	}

	//初始化路径信息
	game->pathNum = file.readLine().toInt();
	for (int i = 0; i < game->towerNum; i++) {
		std::vector<std::pair<double, double>> tmp;
		game->path.insert(game->path.begin(),tmp);
	}
	
	for (int i = 0; i < game->pathNum; i++) {
		QStringList l = QString(file.readLine()).split('+');
		QList<QString>::Iterator it = l.begin();
		for (int j=0; it != l.end()-1; ++j,++it) {
			double a, b;
			splitPair(*it, &a, &b);
			game->path[i].insert(game->path[i].end(), std::pair<double, double>(a, b));
		}
	}
	//初始化近战单位列表
	game->soldierNum = file.readLine().toInt();
	l = QString(file.readLine()).split('+');
	for (int i = 0; i < game->soldierNum; i++) {
		double a, b;
		splitPair(l[i], &a, &b);
		game->soldierList[i].setPosition(QPoint(a, b));
	}
	file.close();
}

//文件信息解析函数
void splitPair(QString pair, double* pa, double* pb) {
	QStringList l = pair.split(',');
	int tmp2 = l[1].size();
	double tmp = l[1].mid(0, l[1].size() - 1).toDouble();
	*pa = l[0].mid(1).toDouble(), *pb = l[1].mid(0,l[1].size()-1).toDouble();
}