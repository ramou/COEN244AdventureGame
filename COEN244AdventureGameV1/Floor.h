#pragma once
#include "Enterable.h"
#include "Key.h"
#include "Item.h"

class Floor :
    public Enterable
{
public:
    virtual char draw() {
        if(getGold() > 0) return '$';
        if (item != nullptr || key != nullptr) return '?';
        return '.';
    }

};

