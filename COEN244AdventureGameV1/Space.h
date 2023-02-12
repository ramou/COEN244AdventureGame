#pragma once
#include <iostream>
#include "Player.h"
class Space
{
public:
	virtual void move(Player& current) {
		p = &current;
	}
	virtual void draw() {
		if (p == nullptr)
			std::cout << ".";
		else std::cout << "@";
	};

private:
	Player* p;

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
	Other(char c) : c(c) {
		std::cout << "Found an unexpected character " << c << std::endl;
	}
private:
	char c;
};