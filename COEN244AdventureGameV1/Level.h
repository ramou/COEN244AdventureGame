#pragma once
#include <fstream>
#include "Space.h"
class Level
{
public:
	Level(std::ifstream &levelFile);
	void draw();


private:
	Space** map;
	int maxLine = 0;
	int lineCount;
	Player p;
};

