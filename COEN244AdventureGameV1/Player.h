#pragma once
#include "Item.h"
#include "Container.h"

class Player
{
public:
	void pickup(Item thing) {
		inventory.put(thing);
	}


private:
	Container<Item> inventory;
};

