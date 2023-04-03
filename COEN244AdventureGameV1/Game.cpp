#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "pch.h"
#include "Game.h"

void Game::play() {
	currentLevel->draw();
	while (true) {
		try {
			char move;
			std::cin >> move;

			switch (move) {
			case 'w':
				currentLevel->currentSpace = &(currentLevel->currentSpace->makeMove('n'));
				break;
			case 'a':
				currentLevel->currentSpace = &(currentLevel->currentSpace->makeMove('w'));
				break;
			case 's':
				currentLevel->currentSpace = &(currentLevel->currentSpace->makeMove('s'));
				break;
			case 'd':
				currentLevel->currentSpace = &(currentLevel->currentSpace->makeMove('e'));
				break;
			default:
				throw InvalidInputException(move);
			}


			//We want a lambda to pick up the items.
			auto pickupFunction = [this](Item i) {
				currentLevel->p.pickup(i);
				std::stringstream mess;
				mess << "You have picked up: " << i.getName();
				currentLevel->messages.push_back(mess.str());
			};

			//Check if there are items and pick them up:
			if (!((Floor*)currentLevel->currentSpace)->items.isEmpty()) {
				((Floor*)currentLevel->currentSpace)->items.process(pickupFunction);
				/*
				messages.push_back("We found these itmes:");
				((Floor*)currentSpace)->items.display(messages);
				*/

				//A good solution might be to use lambdas here
				//Pass a lambda into a container do do something, 
				//up to and inclduing removing stuff
				//Iterate through each item. Give a message that we're
				//picking it up, add it to the player inventory that is passed
				//remove it from the current iterator.

			}

		}/* We don't need this because the InvalidActionException
			Catches both!
		 catch (WalkedIntoWallException& e) {
			messages.push_back(e.toStr());
		}*/  catch (InvalidActionException& e) {
			currentLevel->messages.push_back(e.toStr());
		}

		currentLevel->draw();
	}
}

Game::Game(std::string levelsFile) {

	std::string line;
	//Let's get all possible items from items.txt
	std::ifstream levelFile(levelsFile);
	while (getline(levelFile, line)) {
		std::ifstream levelFile;
		levelFile.open(line);
		levels.push_back(levelFile);
	}

	currentLevel = &levels.at(0);

}
