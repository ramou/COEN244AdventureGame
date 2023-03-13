#pragma once
#include <string>
#include <sstream>

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
class WalkedIntoWallException
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

