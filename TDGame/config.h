#pragma once

#include "menu.h"

//菜单配置函数
void menuConfig(Menu* menu, int i);

//游戏配置函数
void gameConfig(Game* game, int i);

//文件解析函数
void splitPair(QString pair,double* pa,double* pb);