#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

class Map
{
public:ed3rf

	Map(std::ifstream &file) {
		using namespace std;

		string line;
		while (getline(file, line)) {
			mapWidth = line.length();
			++mapHeight;
		}

		file.clear();
		file.seekg(0);

		board = new char[mapWidth * mapHeight];
		int pos = 0;
		while (getline(file, line)) {
			for (char c : line) {
				board[pos] = c;
				if (c == '@') {
					currentPlayerPosition = pos;
					board[pos] = '.';
				}
				++pos;
			}
		}


	}

	void move() {
		char m;
		std::cin >> m;
		int oldPos = currentPlayerPosition;
		switch (m) {
		case 'w':
			currentPlayerPosition -= mapWidth;
			break;

		case 'a':
			--currentPlayerPosition;
			break;

		case 's':
			currentPlayerPosition += mapWidth;
			break;

		case 'd':
			++currentPlayerPosition;
			break;

		default:
			message << "Incorrect move." << std::endl;
		}+`

		switch (board[currentPlayerPosition]) {
		case '#':
			message << "Bang, you hit a wall!" << std::endl;
			currentPlayerPosition = oldPos;
			break;
		case '<':
			message << "You escaped!" << std::endl;
			break;
		}


	}

	void drawMap() {
		system("cls");
		for (int row = 0; row < mapHeight; ++row) {
			for (int col = 0; col < mapWidth; ++col) {
				int pos = row * mapWidth + col;
				if (pos == currentPlayerPosition) {
					std::cout << '@';
				}
				else {
					std::cout << board[pos];
				}
			}
			std::cout << std::endl;
		}
		std::cout << message.str();
		message = {};
	}


private:
	char* board;
	int currentPlayerPosition = 0;
	int mapWidth, mapHeight=0;
	std::stringstream message;





};

