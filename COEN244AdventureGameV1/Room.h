#pragma once
#include <string>
#include "Direction.h"
#include "AdventureException.h"

class Room
{
public:
	

	virtual bool canEnter() = 0;
	virtual Room* attemptMove(const Direction d) {
		switch (d) {
			case Direction::NORTH:
				if(north->canEnter()) return north;
				break;
			case Direction::SOUTH:
				if (south->canEnter()) return south;
				break;
			case Direction::EAST:
				if (east->canEnter()) return east;
				break;
			case Direction::WEST:
				if (west->canEnter()) return west;
				break;
		}
		throw WalkIntoWallException(d);
	}
	virtual char draw() = 0;

	void initializeRooms(Room* north,
		Room* south,
		Room* east,
		Room* west) {
		this->north = north;
		this->south = south;
		this->east = east;
		this->west = west;
	}

private:
	Room *north = nullptr, *south = nullptr, *east = nullptr, *west = nullptr;
};

