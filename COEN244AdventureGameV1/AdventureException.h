#pragma once

#include <string>
#include <sstream>
#include "Direction.h"

class AdventureException {
public:
	virtual std::string what() const = 0;
};


class InvalidMoveException : public AdventureException {

};

class WalkIntoWallException : public InvalidMoveException {
public:
	WalkIntoWallException(Direction d) : d(d) {}

	virtual std::string what() const {
		std::stringstream ss;
		ss << "You bumped into the wall while walking ";
		switch (d) {
		case Direction::NORTH:
			ss << "North";
			break;
		case Direction::SOUTH:
			ss << "South";
			break;
		case Direction::EAST:
			ss << "East";
			break;
		case Direction::WEST:
			ss << "West";
			break;
		}
		ss << "." << std::endl;
		return ss.str();
	}

private:
	Direction d;
};


class BadUserActionException : public AdventureException {
public:
	BadUserActionException(char c) : key(c) {}

	virtual std::string what() const {
		std::stringstream ss;
		ss << "The key '" << key << "' is not used in this game.";
		return ss.str();
	}

private:
	char key;
};