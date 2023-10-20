#pragma once

#include "Map.h"
#include "UIFactory.h"

class Game
{
public:
    Game() : myUI(UIFactory::createUI()){
        std::ifstream mapFile("level1.txt");
        currentLevel = new Map(mapFile);

    }
    
    ~Game() {
        delete currentLevel;
    }


	void play() {

        while (true) {
            myUI->draw(*currentLevel);
            currentLevel->move(myUI->getInput());
        }
	}
private:
    Map *currentLevel;
    std::unique_ptr<AdventureUI> myUI;
};

