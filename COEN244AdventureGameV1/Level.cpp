#include "Level.h"
#include <string>
#include <iostream>

using namespace std;

/*

We take an inputfilestream to a text file that represents our level in
ascii text. We build the level by determining the longest line so we can 
allocate a simple character array. We then read through again, filling in
the dynamically allocated character array.

*/
Level::Level(ifstream& levelFile) {
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

	map = new char[maxLine * lines];
	lines = 0;

	//We loop through all the lines
	//We print the lines to the beginning of 
	//the corresponding line in the dynamic array
	//that represents the level
	while (getline(levelFile, line)) {
		int i;
		for (i = 0; i < line.size(); i++) {
			map[maxLine * lines + i] = line[i];
		}
		//If the map line was short, print spaces
		for (; i < maxLine; i++) {
			map[maxLine * lines + i] = ' ';
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
	for (int y = 0; y < lineCount; y++) {
		for (int x = 0; x < maxLine; x++) {
			cout << map[y*maxLine + x];
		}
		cout << endl;
	}

}
