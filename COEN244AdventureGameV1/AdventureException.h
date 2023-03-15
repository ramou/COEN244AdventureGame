#pragma once
#include <string>
#include <sstream>

class InvalidActionException {
public:
	virtual std::string toStr() = 0;

private:
};

/*
We decided to include exceptions as an 
approach to deal with non-standard behaviours
in moving.

This Exception generally represents hitting a 
wall and it can have its context updated
by the setDirection decorator if that context 
is available. I've also added a constructor
that takes that context for convenience.


*/
class WalkedIntoWallException : public InvalidActionException
{
public:

	WalkedIntoWallException() {}
	WalkedIntoWallException(char dir) {
		setDirection(dir);
	}
	
	std::string toStr() {
		std::stringstream ss;
		ss << "While walking " << direction << " you walked into a wall!";
		return  ss.str();
	}

	void setDirection(char d) {
		switch (d) {
		case 'n':
			direction = "North";
			break;
		case 's':
			direction = "South";
			break;
		case 'e':
			direction = "East";
			break;
		case 'w':
			direction = "West";
			break;
		default:
			break;
		}
	}
	
private:
	std::string direction = "unknown";

};


class InvalidInputException : public InvalidActionException {
public:
	InvalidInputException(char inp) : input{ inp } {}

	std::string toStr() {
		std::stringstream ss;
		ss << "Character " << input << " is not a valid key at this time.";
		return  ss.str();
	}

private:
	char input;
};

class EscapedDungeonException {
public:

	std::string toStr() {
		std::stringstream ss;
		ss << "You win!";
		return  ss.str();
	}
};


