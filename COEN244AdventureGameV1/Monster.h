#pragma once
#include<vector>
#include<sstream>
#include "Obstacle.h"
#include "Item.h"


class Monster : public Obstacle<Item> {
public:
	Monster(Item *sol, std::string n, std::string s, std::string f) : Obstacle::Obstacle(sol), name(n), success(s), fail(f) {}
	
	std::string successfulResolution() override {
		return success;
	}

	std::string failedResolution() override {
		return fail;
	}

private:
	std::string name;
	std::string success;
	std::string fail;
	
};

