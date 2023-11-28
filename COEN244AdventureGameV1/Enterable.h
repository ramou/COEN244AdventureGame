#pragma once
#include <vector>

#include "Room.h"
#include "Item.h"
#include "Key.h"
#include "Door.h"

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

    void addDoor(Door *d) {
        this->door = d;
    }

    virtual Room* attemptMove(const Direction d) {
        Enterable *newRoom = (Enterable*)Room::attemptMove(d);
        if (newRoom->door != nullptr) {
            throw ObstacleException<Enterable, Door>{newRoom, newRoom->door};
        }

        return newRoom;
    }

    Item* item = nullptr;

    Key* key = nullptr;
    Door* door = nullptr;



private:
    int gold = 0;
};

