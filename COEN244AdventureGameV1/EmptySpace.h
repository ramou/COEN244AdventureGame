#pragma once
#include "Space.h"
class EmptySpace :
    public Space
{
    void draw() {
        std::cout << " ";
    }
};

