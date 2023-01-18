#include "Level.h"
#include <string>
#include <iostream>

using namespace std;

Level::Level(ifstream& levelFile) {
	string line;
	int lines = 0;
	while (getline(levelFile, line)) {
		lines++;
		if (line.size() > maxLine) maxLine = line.size();
	}


	levelFile.clear();
	levelFile.seekg(0, ios::beg);


	cout << maxLine << " " << lines << " " << (maxLine*lines) << endl;

	map = new char[maxLine * lines];
	lines = 0;
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

void Level::draw()
{
	for (int y = 0; y < lineCount; y++) {
		for (int x = 0; x < maxLine; x++) {
			cout << map[y*maxLine + x];
		}
		cout << endl;
	}

}
