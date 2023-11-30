#pragma once

#include "Map.h"
#include "UIFactory.h"
#include "Player.h"
#include "Key.h"
#include "Door.h"
#include "Monster.h"
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

            std::cout << c << " " << obType << " " << name << std::endl;

            if (obType.find("Door") == 0) {
                Key* k = nullptr;
                for (Key* aKey : allKeys) {
                    if (aKey->name.find(name) == 0) k = aKey;
                }
                if (k == nullptr) throw std::string("Couldn't find a matching key!");
                Door* d = new Door(k);
                doors.insert(std::make_pair(c, d));
            } else {
                std::string sol;
                std::string success, failure;
                lineData >> sol;
                std::getline(obstacleFile, failure);
                std::getline(obstacleFile, success);

                Item* i = nullptr;
                for (Item* aItem : allItems) {
                    if (aItem->name.find(sol) == 0) i = aItem;
                }
                if (i == nullptr) throw std::string("Couldn't find a matching key!");
                Monster* m = new Monster(i, name, success, failure);
                monsters.insert(std::make_pair(c, m));

            }
        }

        std::ifstream mapFile("level1.txt");
        currentLevel = new Map(mapFile, currentPlayer, keys, items, doors, monsters);

    }

    //How is there no trim function already defined? Barbarism!
    //https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
    inline std::string trim(const std::string& s)
    {
        auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
        auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
        return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
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
    std::map<char, Monster*> monsters;


    


};

