#pragma once
#include <iostream>
#include <vector>
#include "Enterable.h"
#include "Key.h"
#include "Item.h"


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
		
		for (auto i : player.inventory) {
			os << "Current Player has item " << i->name << std::endl;
		}

		for (auto i : player.keys) {
			os << "Current Player has key " << i->name << std::endl;
		}
		
		return os;
	}

	Player& operator+=(Enterable* room) {
		gold += room->getGold();
		room->setGold(0);

		// Eventually, pick up items as well
		return *this;
	}
	std::vector<Key*> keys;
	std::vector<Item*> inventory;
private:
	int gold = 0;
	
};

