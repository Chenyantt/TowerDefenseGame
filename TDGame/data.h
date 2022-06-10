#pragma once

#include <qmap.h>
#include <vector>

//窗口的长度与宽度
extern const int WIDTH;
extern const int HEIGHT;
extern const QString TITLE;

//关卡列表
#define LEVELNUM 5
extern const std::vector<int> LEVELLIST;

//根据配置文件加载远程单位的列表
extern const QMap<QString, int> TOWERLIST;
extern const QMap<QString, double> TOWERRANGE;
extern const QMap<QString, int> TOWERATK;
extern const QMap<QString, int> TOWERATKTYPE;

//根据配置文件加载近战单位的列表
extern const QMap<QString, int> SOLDIERLIST;
extern const QMap<QString, int> SOLDIERHEALTH;
extern const QMap<QString, int> SOLDIERATK;
extern const QMap<QString, int> SOLDIERATKTYPE;
extern const QMap<QString, int> SOLDIERRANGE;
extern const QMap<QString, int> SOLDIERBLOCK;
