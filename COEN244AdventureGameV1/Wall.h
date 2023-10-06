#pragma once
#include "NonEnterable.h"
class Wall :
    public NonEnterable
{
public:
    virtual char draw() {
        return '#';
    }
};

