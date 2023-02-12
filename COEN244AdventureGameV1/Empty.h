#pragma once
#include "Space.h"
class Empty :
    public Space
{
    void draw(Player& current) {
        std::cout << " ";
    }
};

