#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Level.h"
#include "Item.h"
class Game
{
public:
	Game(std::string levelsFile);

	void play();

private:
	std::vector<Level> levels;
	Level* currentLevel;
};

