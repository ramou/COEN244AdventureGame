#pragma once
#include "Space.h"
class Wall :
    public Space
{
    void draw() {
        std::cout << "#";
    }

};

