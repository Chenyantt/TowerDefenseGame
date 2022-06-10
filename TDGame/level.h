#pragma once

#include <QMainWindow>

#include "map.h"
#include "game.h"

class Game;

class Level : public QMainWindow
{
	Q_OBJECT

public:
	Level(int i, Map* parent);
private:
	Map* parent;
	Game* game;
};