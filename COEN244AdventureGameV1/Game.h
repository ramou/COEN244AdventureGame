#pragma once

#include "Map.h"
#include "UIFactory.h"
#include "Player.h"

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
            char action = myUI->getInput();
            if (action == 'q') {
                //We'll output the status
                currentLevel->messages() << currentPlayer;
            } else {
                currentLevel->move(action);
                if (currentLevel->getCurrentRoom()->getGold() > 0) {
                    int g = currentLevel->getCurrentRoom()->getGold();
                    currentPlayer += currentLevel->getCurrentRoom();
                    currentLevel->messages() << "We just picked up " << g << " gold!" << std::endl;
                }
            }
        }
	}

private:
    Map *currentLevel;
    std::unique_ptr<AdventureUI> myUI;
    Player currentPlayer;
};

