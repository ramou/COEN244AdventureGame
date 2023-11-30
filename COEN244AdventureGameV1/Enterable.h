#pragma once
#include <vector>

#include "Room.h"
#include "Item.h"
#include "Key.h"
#include "Door.h"
#include "Monster.h"

class Enterable :
    public Room
{
public:
    bool canEnter() {
        return true;
    }

    int getGold() const {
        return gold;
    }

    void setGold(int g) {
        gold = g;
    }

    void addKey(Key* key) {
        this->key = key;
    }

    void addItem(Item* item) {
        this->item = item;
    }

    void addDoor(Door* d) {
        this->door = d;
    }

    void addMonster(Monster* m) {
        this->monster = m;
    }

    virtual Room* attemptMove(const Direction d) {
        Enterable *newRoom = (Enterable*)Room::attemptMove(d);
        if (newRoom->door != nullptr) {
            throw ObstacleException<Enterable, Door>{newRoom, newRoom->door};
        }

        if (newRoom->monster != nullptr) {
            throw ObstacleException<Enterable, Monster>{newRoom, newRoom->monster};
        }

        return newRoom;
    }

    Item* item = nullptr;

    Key* key = nullptr;
    Door* door = nullptr;
    Monster* monster = nullptr;



private:
    int gold = 0;
};

