#pragma once
#include <iostream>
#include "Player.h"
#include "ISpace.h"

class Space : public ISpace
{
public:
	Space(ISpace& defaultSpace) : north(&defaultSpace), 
		south(&defaultSpace),
		east(&defaultSpace),
		west(&defaultSpace) {}

	void setPlayer(Player* p) {
		currentPlayer = p;
	}

	virtual ISpace& move(ISpace& origin) {
		return *this;
	}

	virtual ISpace& makeMove(char m) {
		switch (m) {
		case 'n':
			return north->move(*this);
			
		case 's':
			return south->move(*this);
			
		case 'w':
			return west->move(*this);
			
		case 'e':
			return east->move(*this);

		}
		return east->move(*this);

	}


	virtual void draw() {
		if (currentPlayer == nullptr)
			std::cout << ".";
		else std::cout << "@";
	};

	void setNorth(ISpace& s) { north = &s; }
	void setSouth(ISpace& s) { south = &s; }
	void setEast(ISpace& s) { east = &s; }
	void setWest(ISpace& s) { west = &s; }

private:
	Player* currentPlayer = nullptr;
	ISpace* north;
	ISpace* south;
	ISpace* east;
	ISpace* west;

};


//It broke because we didn't check for a bunch
//of the other things like items, stairs or the
//"other" player starting position from the map
//we grabbed. Instead of dying horribly, when
//we start up, how about this to notify the user
//and keep goind?
class Other :
	public Space
{
public:
	Other(Space def, char c) : Space(def), c(c) {
		std::cout << "Found an unexpected character " << c << std::endl;
	}
private:
	char c;
};