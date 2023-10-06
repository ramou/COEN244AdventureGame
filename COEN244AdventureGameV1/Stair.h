#pragma once
#include "Enterable.h"
class Stair :
    public Enterable
{
public:
    virtual char draw() {
        return getGold() > 0 ? '$' : '<';
    }
};

