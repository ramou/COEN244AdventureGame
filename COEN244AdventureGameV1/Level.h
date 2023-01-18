#pragma once
#include <fstream>
class Level
{
public:
	Level(std::ifstream &levelFile);
	void draw();


private:
	char* map;
	int maxLine = 0;
	int lineCount;
};

