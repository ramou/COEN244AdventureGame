#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <random>

#include "Room.h"
#include "Direction.h"
#include "Screen.h"
#include "RoomFactory.h"
#include "AdventureException.h"
#include <vector>
#include <algorithm>
#include <map>
#include "Key.h"
#include "Map.h"
#include "Door.h"
#include "Monster.h"
#include "Player.h"

class Map : public Screen {
public:

	Map(std::ifstream &file, Player &p, std::map<char, Key*> keys, std::map<char, Item*> items, std::map<char, Door*> doors, std::map<char, Monster*> monsters) : currentPlayer(p) {

		std::vector<Room*> rooms;

		using namespace std;

		string line;
		while (getline(file, line)) {
			mapWidth = (int)line.length();
			++mapHeight;
		}

		file.clear();
		file.seekg(0);

		board = new Room*[mapWidth * mapHeight];
		int pos = 0;
		while (getline(file, line)) {
			for (char c : line) {
				if (pos > mapWidth * mapHeight) break;//Just to kill the warning...
				board[pos] = RoomFactory::create(c);
				if (board[pos]->canEnter()) {
					rooms.push_back(board[pos]);
					if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
						//It's something special!!!

						auto key = keys.find(c);
						if (key != keys.end()) {
							((Floor*)board[pos])->addKey(key->second);
						}

						auto item = items.find(c);
						if (item != items.end()) {
							((Floor*)board[pos])->addItem(item->second);
						}

						auto door = doors.find(c);
						if (door != doors.end()) {
							((Floor*)board[pos])->addDoor(door->second);
						}

						auto monster = monsters.find(c);
						if (monster != monsters.end()) {
							((Floor*)board[pos])->addMonster(monster->second);
						}
					}
				}

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
		}
		catch (std::string m) {
			message << m << std::endl;
		}
		catch (ObstacleException<Enterable, Door>& d) {
			if (d.obstacle->attemptResolution(currentPlayer.keys)) {
				auto& keys = currentPlayer.keys;
				auto sol = d.obstacle->getSolution();
				auto it = std::remove(keys.begin(), keys.end(), sol);
				keys.erase(it, keys.end());
				d.room->door = nullptr;
				message << d.obstacle->successfulResolution();
				currentPlayerRoom = d.room;
			}
			else {
				message << d.obstacle->failedResolution();
			}
		}
		catch (ObstacleException<Enterable, Monster>& m) {
			if (m.obstacle->attemptResolution(currentPlayer.inventory)) {
				auto& inventory = currentPlayer.inventory;
				auto sol = m.obstacle->getSolution();
				auto it = std::remove(inventory.begin(), inventory.end(), sol);
				inventory.erase(it, inventory.end());
				m.room->monster = nullptr;
				message << m.obstacle->successfulResolution();
				currentPlayerRoom = m.room;
			}
			else {
				message << m.obstacle->failedResolution();
			}
		}
	}

	Direction getMove(char m) {
		switch (m) {
		case 'a':
			return Direction::WEST;
		case 'w':
			return Direction::NORTH;
		case 's':
			return Direction::SOUTH;
		case 'd':
			return Direction::EAST;
		default:
			throw BadUserActionException(m);
		}

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
	Player& currentPlayer;
	Room** board;
	Room *currentPlayerRoom = nullptr;
	int mapWidth=0, mapHeight=0;
	std::stringstream message;
};


