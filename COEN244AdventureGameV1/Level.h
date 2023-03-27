#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Item.h"
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
	int mapWidth = 0;
	int mapHeight;
	Player p;
	ISpace *currentSpace;

	std::map<char, Item> allItems;

};

