#include "pch.h"
#include "Level.h"
#include <string>
#include <iostream>
#include "EmptySpace.h"
#include "Wall.h"
#include "Stairs.h"


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

	map = new Space*[maxLine * lines];
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
				map[maxLine * lines + i] = new Wall();
				break;
			case '@' :
				map[maxLine * lines + i] = new Space();
				map[maxLine * lines + i]->move(p);
				break;
			case '.':
				map[maxLine * lines + i] = new Space();
				break;
			default:
				map[maxLine * lines + i] = new Other(line[i]);
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

}


/*

We draw the board as text.

*/
void Level::draw()
{
	using namespace std;
	for (int y = 0; y < lineCount; y++) {
		for (int x = 0; x < maxLine; x++) {
			map[y*maxLine + x]->draw();
		}
		cout << endl;
	}

}
