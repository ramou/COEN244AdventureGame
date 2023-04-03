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

	ISpace* currentSpace;
	std::vector<std::string> messages;
	Player p;
private:
	
	ISpace** map;
	int mapWidth = 0;
	int mapHeight;
	
	

	std::map<char, std::vector<Item>> allItems;

};

