#pragma once
#include "Wall.h"
#include "Floor.h"
#include "Stair.h"
#include "Sentinel.h"
class RoomFactory {
public:
	static Sentinel SENTINEL;
	static Room* create(char c) {
		switch (c) {
		case '.':
			return new Floor();
		case '@':
			return new Floor();
		case '<':
			return new Stair();
		case '#':
			return new Wall();
		default: 
			//We want this to be a floor since it find a obstacle or solution
			return new Floor();
		}


	}

};



