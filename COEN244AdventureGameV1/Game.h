#pragma once

#include "Map.h"
#include "UIFactory.h"
#include "Player.h"
#include "Key.h"
#include "Door.h"
#include "Item.h"
#include <string>
#include <sstream>

#include <map>


class Game
{
public:
    Game() : myUI(UIFactory::createUI()){
        
        std::ifstream solutionFile("Solutions.txt");
        std::string line; 
        while (std::getline(solutionFile, line)) {
            std::stringstream lineData(line);
            char c;
            std::string solType;
            std::string name;
            lineData >> c >> solType >> name;

            if (solType.find("Key")==0) {
                Key* s = new Key(name);
                allKeys.push_back(s);
                keys.insert(std::make_pair(c, s));
            } else {
                Item* s = new Item(name);
                allItems.push_back(s);
                items.insert(std::make_pair(c, s));
            }
        }

        std::ifstream obstacleFile("Obstacles.txt");
        while (std::getline(obstacleFile, line)) {
            std::stringstream lineData(line);
            char c;
            std::string obType;
            std::string name;
            lineData >> c >> obType >> name;

            if (obType.find("Door") == 0) {
                Key* k = nullptr;
                for (Key* aKey : allKeys) {
                    if (aKey->name.find(name) == 0) k = aKey;
                }
                if (k == nullptr) throw std::string("Couldn't find a matching key!");
                Door* d = new Door(k);
                doors.insert(std::make_pair(c, d));
            }
            else {
                //Eventually do Monsters
            }
        }

        std::ifstream mapFile("level1.txt");
        currentLevel = new Map(mapFile, currentPlayer, keys, items, doors);

    }
    
    ~Game() {
        delete currentLevel;
    }


	void play() {

        while (true) {
            try {
                myUI->draw(*currentLevel);
                char action = myUI->getInput();
                if (action == 'q') {
                    //We'll output the status
                    currentLevel->messages() << currentPlayer;
                }
                else {
                    currentLevel->move(action);
                    if (currentLevel->getCurrentRoom()->getGold() > 0) {
                        int g = currentLevel->getCurrentRoom()->getGold();
                        currentPlayer += currentLevel->getCurrentRoom();
                        currentLevel->messages() << "We just picked up " << g << " gold!" << std::endl;
                    }
                    
                    if (currentLevel->getCurrentRoom()->item != nullptr) {
                        currentPlayer.inventory.push_back(currentLevel->getCurrentRoom()->item);
                        currentLevel->messages() << "We just picked up a " << currentLevel->getCurrentRoom()->item->name << std::endl;
                        currentLevel->getCurrentRoom()->item = nullptr;
                    }

                    if (currentLevel->getCurrentRoom()->key != nullptr) {
                        currentPlayer.keys.push_back(currentLevel->getCurrentRoom()->key);
                        currentLevel->messages() << "We just picked up a " << currentLevel->getCurrentRoom()->key->name << " key" << std::endl;
                        currentLevel->getCurrentRoom()->key = nullptr;                        
                    }

                }
            }
            catch (const AdventureException &e) {
                currentLevel->messages() << e.what() << std::endl;
            }
        }
	}

private:
    Map *currentLevel;
    std::unique_ptr<AdventureUI> myUI;
    Player currentPlayer;


    std::vector<Key*> allKeys;
    std::vector<Item*> allItems;
    std::map<char, Key*> keys;
    std::map<char, Item*> items;
    std::map<char, Door*> doors;
    /*
    * // Key -> Value 
    * 
    
    std::map<char, Monster*> monsters;
    
    */


};

