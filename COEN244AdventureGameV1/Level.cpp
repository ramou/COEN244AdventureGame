#include "pch.h"
#include "Level.h"
#include <string>
#include <iostream>
#include "ISpace.h"
#include <stdlib.h>

/*

We take an inputfilestream to a text file that represents our level in
ascii text. We build the level by determining the longest line so we can 
allocate a simple character array. We then read through again, filling in
the dynamically allocated character array.

*/
Level::Level(std::ifstream& levelFile) {
	using namespace std;
	string line;
	int lines = 0;

	//We loop through all the lines
	//looking for the longest line
	while (getline(levelFile, line)) {
		lines++;
		if (line.size() > mapWidth) mapWidth = (int)line.size();
	}


	/*
	We got to the end of the file while looking for the longest line.
	In order to use it again, we need to clear the eof flag, and then
	point back to the beginning of the file. Then we can treat it like
	we had just newly opened it.
	*/
	levelFile.clear();
	levelFile.seekg(0, ios::beg);


	cout << mapWidth << " " << lines << " " << (mapWidth*lines) << endl;

	map = new ISpace*[mapWidth * lines];
	lines = 0;

	//We loop through all the lines
	//We print the lines to the beginning of 
	//the corresponding line in the dynamic array
	//that represents the level
	while (getline(levelFile, line)) {
		int i;
		for (i = 0; i < line.size(); i++) {
			switch (line[i]) {
			case '#' :
				map[mapWidth * lines + i] = Wall::WALL;
				break;
			case '@' :
				map[mapWidth * lines + i] = new Floor();
				currentSpace = map[mapWidth * lines + i];
				break;
			case '.':
				map[mapWidth * lines + i] = new Floor();
				break;
			default:
				map[mapWidth * lines + i] = new OtherSpace(line[i]);
				break;
			}
			
		}
		//If the map line was short, print spaces
		for (; i < mapWidth; i++) {
			map[mapWidth * lines + i] = new VoidSpace();
		}
		lines++;
	}
	mapHeight = lines;

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (y > 0) 
				map[y * mapWidth + x]->setNorth(*map[(y - 1) * mapWidth + x]);
			if (y < (mapHeight-1))
				map[y * mapWidth + x]->setSouth(*map[(y + 1) * mapWidth + x]);
			if (x > 0)
				map[y * mapWidth + x]->setWest(*map[y * mapWidth + x-1]);
			if (x < (mapWidth-1))
				map[y * mapWidth + x]->setEast(*map[y * mapWidth + x + 1]);
		}

		
	}

}


/*

We draw the board as text.

*/
void Level::draw()
{
	system("CLS");
	using namespace std;
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (map[y * mapWidth + x] == currentSpace) cout << '@';
			else map[y * mapWidth + x]->draw();
		}
		cout << endl;
	}

}

void Level::play()
{
	draw();
	while (true) {
		char move;
		std::cin >> move;
		ISpace* newSpace = nullptr;
		switch (move) {
		case 'w':
			newSpace = &currentSpace->makeMove('n');
			break;
		case 'a':
			newSpace = &currentSpace->makeMove('w');
			break;
		case 's':
			newSpace = &currentSpace->makeMove('s');
			break;
		case 'd':
			newSpace = &currentSpace->makeMove('e');
			break;
		default:
			continue;
		}

		currentSpace = newSpace;		

		draw();
	}

}
