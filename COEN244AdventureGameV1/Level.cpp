//Ignore pch.h, it's has to do with the testing framework
#include "pch.h"

#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>

#include "Level.h"
#include "ISpace.h"
#include "AdventureException.h"

/*

We take an inputfilestream to a text file that represents our level.
The first two lines represent files of maps to items or obstacles, the rest
is our map in ascii text. We build the level by determining the longest line 
so we can allocate a simple character array. We then read through again, filling 
in the dynamically allocated character array.

*/
Level::Level(std::ifstream& levelFile) {
	using namespace std;
	string line;
	int lines = 0;

	//First line of the level file is the items file location:
	string itemFileName;
	getline(levelFile, itemFileName);
	//Second line of the level file is the obstacle file location:
	string obstacleFileName;
	getline(levelFile, obstacleFileName);

	//Let's get all possible items from items.txt
	std::ifstream itemFile(itemFileName);
	while (getline(itemFile, line)) {
		//Check if there's an entry in the map for that character
		if (allItems.find(line.at(0)) != allItems.end()) {
			//Already some items, just add to the pile
			vector<Item> &stuff = allItems.find(line.at(0))->second;
			stuff.push_back(line.substr(2));
		} else {
			//No items yet, make a new pile
			vector<Item> stuff;
			stuff.push_back(line.substr(2));
			allItems.insert(std::pair<char, std::vector<Item>>(line.at(0), stuff));
		}

	}


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

	//Skip the first two lines as they don't actually hold map info
	getline(levelFile, line);
	getline(levelFile, line);


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
			case '<':
				map[mapWidth * lines + i] = new Stairs();
				break;
			default:
				
				//map::end.
				std::map<char, std::vector<Item>>::iterator pileOfItems;

				pileOfItems = allItems.find(line[i]);
				if (pileOfItems != allItems.end()) {
					map[mapWidth * lines + i] = new Floor();
					((Floor*)map[mapWidth * lines + i])->items.put(pileOfItems->second);
				} else {
					map[mapWidth * lines + i] = new OtherSpace(line[i]);
				}
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
void Level::draw() {

	system("CLS");
	using namespace std;
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (map[y * mapWidth + x] == currentSpace) cout << '@';
			else map[y * mapWidth + x]->draw();
		}
		cout << endl;
	}

	for (auto& m : messages) {
		cout << m << endl;
	}
	messages.clear();

}
