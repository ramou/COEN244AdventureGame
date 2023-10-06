#pragma once
class Room
{
public:
	enum Direction {NORTH, SOUTH, EAST, WEST};

	virtual bool canEnter() = 0;
	virtual Room* attemptMove(Direction d) {
		switch (d) {
			case NORTH:
				if(north->canEnter()) return north;
				break;
			case SOUTH:
				if (south->canEnter()) return south;
				break;
			case EAST:
				if (east->canEnter()) return east;
				break;
			case WEST:
				if (west->canEnter()) return west;
				break;
		}
		return this;
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

