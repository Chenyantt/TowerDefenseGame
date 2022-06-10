#include "data.h"

const int WIDTH = 1070;
const int HEIGHT = 670;
const QString TITLE = "皇城突袭";

const std::vector<int> LEVELLIST = {1,1,1,2,2};

const QMap<QString, int> TOWERLIST = { {"archer",70},{"icy",70},{"mage",100},{"canon",120} };

const QMap<QString, double> TOWERRANGE = { {"archer",150},{"icy",0},{"mage",140},{"canon",140} };

const QMap<QString, int> TOWERATK = { {"archer",10},{"icy",0},{"mage",15},{"canon",20} };

const QMap<QString, int> TOWERATKTYPE= { {"archer",2},{"icy",0},{"mage",2},{"canon",1} };

const QMap<QString, int> SOLDIERATK = { {"warrior",2},{"wall",0},{"wizzard",6}};

const QMap<QString, int> SOLDIERATKTYPE= { {"warrior",1},{"wall",0},{"wizzard",2} };

const QMap<QString, int> SOLDIERLIST = { {"warrior",25},{"wall",20},{"wizzard",30} };

const QMap<QString, int> SOLDIERRANGE = { {"warrior",25},{"wall",0},{"wizzard",80} };

const QMap<QString, int> SOLDIERBLOCK = { {"warrior",1},{"wall",3},{"wizzard",1} };

const QMap<QString, int> SOLDIERHEALTH = { {"warrior",75},{"wall",200},{"wizzard",40}};