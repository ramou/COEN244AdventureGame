#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "ISpace.h"
#include "Player.h"
class Level
{
public:
	Level(std::ifstream &levelFile);
	void draw();
	void play();

private:
	std::vector<std::string> messages;
	ISpace** map;
	int maxLine = 0;
	int lineCount;
	Player p;
	ISpace *currentSpace;
};

