#pragma once
#include "Room.h"

#include "Item.h"
#include "Key.h"

class Enterable :
    public Room
{
public:
    bool canEnter() {
        return true;
    }

    int getGold() {
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

    Item* item = nullptr;

    Key* key = nullptr;

private:
    int gold = 0;
};

