#pragma once
#include <sstream>
#include <vector>
#include "Obstacle.h"
#include "Key.h"


class Door: public Obstacle<Key>
{
public:
	Door(Key *k) : Obstacle(k) {};

	std::string successfulResolution() override  {
		std::stringstream bruce;
		bruce << "You were able to unlock the door with your " << getSolution()->name << " key!" << std::endl;
		return bruce.str();
	}

	std::string failedResolution() override {
		std::stringstream bruce;
		bruce << "None of your keys were able to unlock this " << getSolution()->name << " lock  :(" << std::endl;
		return bruce.str();
	}

};

