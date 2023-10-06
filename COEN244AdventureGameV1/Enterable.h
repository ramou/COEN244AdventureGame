#pragma once
#include "Room.h"
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

private:
    int gold;
};

