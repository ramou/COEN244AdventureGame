#pragma once
#include "Floor.h"
#include <vector>

class Portal :
    public Floor {
public:

    virtual char draw() {
        if (getGold() > 0) return '$';
        if (monster != nullptr) return 'M';
        if (door != nullptr) return '+';
        if (item != nullptr || key != nullptr) return '?';

        return 'P';
    }

    Portal *getTwin(std::vector<Portal*> portals) {
        for(int i = 0; i < portals.size(); ++i) {
            Portal* p = portals[i];
            if (p == this) {
                return portals[portals.size() - i - 1];
            }
        }

        return this;
    }


};

