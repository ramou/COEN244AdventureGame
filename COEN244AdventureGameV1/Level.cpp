#include "pch.h"
#include "Level.h"
#include <string>
#include <iostream>
#include "Wall.h"
#include "Space.h"
#include "Stairs.h"
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
		if (line.size() > maxLine) maxLine = line.size();
	}


	/*
	We got to the end of the file while looking for the longest line.
	In order to use it again, we need to clear the eof flag, and then
	point back to the beginning of the file. Then we can treat it like
	we had just newly opened it.
	*/
	levelFile.clear();
	levelFile.seekg(0, ios::beg);


	cout << maxLine << " " << lines << " " << (maxLine*lines) << endl;

	map = new ISpace*[maxLine * lines];
	lines = 0;

	//We loop through all the lines
	//We print the lines to the beginning of 
	//the corresponding line in the dynamic array
	//that represents the level
	Wall *aWall = new Wall();
	while (getline(levelFile, line)) {
		int i;
		for (i = 0; i < line.size(); i++) {
			switch (line[i]) {
			case '#' :
				map[maxLine * lines + i] = aWall;
				break;
			case '@' :
				map[maxLine * lines + i] = new Space(*aWall);
				((Space *)map[maxLine * lines + i])->setPlayer(&p);
				currentSpace = map[maxLine * lines + i];
				break;
			case '.':
				map[maxLine * lines + i] = new Space(*aWall);
				break;
			default:
				map[maxLine * lines + i] = new Other(*aWall, line[i]);
				break;
			}
			
		}
		//If the map line was short, print spaces
		for (; i < maxLine; i++) {
			map[maxLine * lines + i] = new EmptySpace();
		}
		lines++;
	}
	lineCount = lines;

	for (int y = 0; y < lineCount; y++) {
		for (int x = 0; x < maxLine; x++) {
			if (y > 0) 
				map[y * maxLine + x]->setNorth(*map[(y - 1) * maxLine + x]);
			if (y < (lineCount-1))
				map[y * maxLine + x]->setSouth(*map[(y + 1) * maxLine + x]);
			if (x > 0)
				map[y * maxLine + x]->setWest(*map[y * maxLine + x-1]);
			if (x < (maxLine-1))
				map[y * maxLine + x]->setEast(*map[y * maxLine + x + 1]);
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
	for (int y = 0; y < lineCount; y++) {
		for (int x = 0; x < maxLine; x++) {
			map[y*maxLine + x]->draw();
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
		
		((Space*)currentSpace)->setPlayer(nullptr);
		currentSpace = newSpace;
		((Space*)currentSpace)->setPlayer(&p);

		draw();
	}

}
