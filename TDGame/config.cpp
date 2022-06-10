#include "config.h"

#include <qfile.h>

//�˵����ú���
void menuConfig(Menu* menu, int i) {
	QFile file(QString("./level%1.txt").arg(QString::number(i)));
	file.open(QIODevice::ReadOnly);
	//��ʼ����Ǯ������ֵ�����ﲨ��
	menu->life = file.readLine().toInt();
	menu->money= file.readLine().toInt();
	menu->boutCount.second= file.readLine().toInt();
	menu->boutCount.first = 0;
	file.close();
}

//��Ϸ���ú���
void gameConfig(Game* game, int i) {
	QFile file(QString("./level%1.txt").arg(QString::number(i)));
	file.open(QIODevice::ReadOnly);
	for (int i = 0; i < 3; ++i) {
		file.readLine();
	}
	//��ʼ��Զ�̵�λ�б�
	game->towerNum= file.readLine().toInt();
	QStringList l = QString(file.readLine()).split('+');
	for (int i = 0; i < game->towerNum; i++) {
		double a, b;
		splitPair(l[i], &a, &b);
		game->towerList[i].setPos(QPoint(a,b));
	}

	//��ʼ��·����Ϣ
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
	//��ʼ����ս��λ�б�
	game->soldierNum = file.readLine().toInt();
	l = QString(file.readLine()).split('+');
	for (int i = 0; i < game->soldierNum; i++) {
		double a, b;
		splitPair(l[i], &a, &b);
		game->soldierList[i].setPosition(QPoint(a, b));
	}
	file.close();
}

//�ļ���Ϣ��������
void splitPair(QString pair, double* pa, double* pb) {
	QStringList l = pair.split(',');
	int tmp2 = l[1].size();
	double tmp = l[1].mid(0, l[1].size() - 1).toDouble();
	*pa = l[0].mid(1).toDouble(), *pb = l[1].mid(0,l[1].size()-1).toDouble();
}