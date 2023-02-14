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
	int maxLine = 0;
	int lineCount;
	Player p;
	ISpace *currentSpace;
};

