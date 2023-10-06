#pragma once
#include "Room.h"
class NonEnterable : public Room {
public:
    virtual char draw() {
        return ' ';
    }

    bool canEnter() {
        return false;
    }
};

