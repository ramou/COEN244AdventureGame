#pragma once
#include "Item.h"
#include "Container.h"

class Player
{
	void pickup(Item thing) {
		inventory.put(thing);
	}


private:
	Container<Item> inventory;
};

