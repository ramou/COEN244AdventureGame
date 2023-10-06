#pragma once
#include "Enterable.h"
class Floor :
    public Enterable
{
public:
    virtual char draw() {
        return getGold() > 0 ? '$':'.';
    }

};

