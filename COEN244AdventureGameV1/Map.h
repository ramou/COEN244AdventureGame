#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <random>

#include "Room.h"
#include "Screen.h"
#include "RoomFactory.h"
#include <vector>
#include <algorithm>

class Map : public Screen {
public:

	Map(std::ifstream &file) {

		std::vector<Room*> rooms;

		using namespace std;

		string line;
		while (getline(file, line)) {
			mapWidth = line.length();
			++mapHeight;
		}

		file.clear();
		file.seekg(0);

		board = new Room*[mapWidth * mapHeight];
		int pos = 0;
		while (getline(file, line)) {
			for (char c : line) {
				board[pos] = RoomFactory::create(c);
				if (board[pos]->canEnter()) rooms.push_back(board[pos]);
				if (c == '@') {
					currentPlayerRoom = board[pos];
				}
				++pos;
			}
		}

		for (int row = 0; row < mapHeight; ++row) {
			for (int col = 0; col < mapWidth; ++col) {
				int pos = row * mapWidth + col;
				Room* n = &RoomFactory::SENTINEL;
				Room* s = &RoomFactory::SENTINEL;
				Room* w = &RoomFactory::SENTINEL;
				Room* e = &RoomFactory::SENTINEL;

				if (col > 0) {
					w = board[pos - 1];
				}
				if (col < mapWidth-1) {
					e = board[pos + 1];
				}

				if (row > 0) {
					n = board[pos - mapWidth];
				}
				if (row < mapHeight - 1) {
					s = board[pos + mapWidth];
				}

				board[pos]->initializeRooms(n, s, e, w);
			}
			
		}

		std::random_device rd;  // Non-deterministic random number generator
		std::mt19937 g(rd());   // Seed with rd
		std::uniform_int_distribution<int> dist(1, 100);

		std::shuffle(rooms.begin(), rooms.end(), g);

		((Enterable*)rooms[0])->setGold(dist(g));
		((Enterable*)rooms[1])->setGold(dist(g));
		((Enterable*)rooms[2])->setGold(dist(g));

	}

	void move(char direction) {
		try {
			currentPlayerRoom = currentPlayerRoom->attemptMove(getMove(direction));
		} catch (std::string m) {
			message << m << std::endl;
		}
	}

	Room::Direction getMove(char m) {
		switch (m) {
		case 'a':
			return Room::WEST;
		case 'w':
			return Room::NORTH;
		case 's':
			return Room::SOUTH;
		case 'd':
			return Room::EAST;
		}
		return  Room::NORTH;
	}

	virtual std::string line(int lineNumber) {
		std::stringstream out;
		for (int col = 0; col < mapWidth; ++col) {
			int pos = lineNumber * mapWidth + col;
			if (board[pos] == currentPlayerRoom) {
				out << '@';
			}
			else {
				out << board[pos]->draw();
			}
		}
		return out.str();
	}

	virtual int numberOfLines() {
		return mapHeight;
	}

	std::stringstream& messages() {
		return message;
	}

	Enterable * getCurrentRoom() {
		return (Enterable *)currentPlayerRoom;
	}

private:
	Room** board;
	Room *currentPlayerRoom;
	int mapWidth=0, mapHeight=0;
	std::stringstream message;





};


