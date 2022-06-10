#pragma once

#include <qmap.h>
#include <vector>

//���ڵĳ�������
extern const int WIDTH;
extern const int HEIGHT;
extern const QString TITLE;

//�ؿ��б�
#define LEVELNUM 5
extern const std::vector<int> LEVELLIST;

//���������ļ�����Զ�̵�λ���б�
extern const QMap<QString, int> TOWERLIST;
extern const QMap<QString, double> TOWERRANGE;
extern const QMap<QString, int> TOWERATK;
extern const QMap<QString, int> TOWERATKTYPE;

//���������ļ����ؽ�ս��λ���б�
extern const QMap<QString, int> SOLDIERLIST;
extern const QMap<QString, int> SOLDIERHEALTH;
extern const QMap<QString, int> SOLDIERATK;
extern const QMap<QString, int> SOLDIERATKTYPE;
extern const QMap<QString, int> SOLDIERRANGE;
extern const QMap<QString, int> SOLDIERBLOCK;
