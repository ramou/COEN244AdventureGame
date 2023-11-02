#pragma once
#include <iostream>
#include "Enterable.h"

class Player
{
public:
	int getGold() const{
		return gold;
	}

	void setGold(int g) {
		gold = g;
	}

	friend std::ostream& operator<<(std::ostream& os, const Player& player) {
		os << "Current Player has " << player.getGold() << " gold." << std::endl;
		return os;
	}

	Player& operator+=(Enterable* room) {
		gold += room->getGold();
		room->setGold(0);
		// Eventually, pick up items as well
		return *this;
	}

private:
	int gold = 0;
};

