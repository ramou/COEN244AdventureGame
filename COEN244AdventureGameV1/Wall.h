#pragma once
#include "ISpace.h"
#include <iostream>
class Wall :
    public ISpace
{
    void draw() {
        std::cout << "#";
    }

    virtual ISpace& move(ISpace& origin) {
        return origin;
    }

    virtual ISpace& makeMove(char m) {
        return *this;
    }

};

class EmptySpace :
    public Wall
{
    void draw() {
        std::cout << " ";
    }
};