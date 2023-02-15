#pragma once
#include <fstream>
#include "ISpace.h"
#include "Player.h"
class Level
{
public:
	Level(std::ifstream &levelFile);
	void draw();
	void play();


private:
	ISpace** map;
	int mapWidth = 0;
	int mapHeight;
	Player p;
	ISpace *currentSpace;
};

