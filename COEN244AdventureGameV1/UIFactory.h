#pragma once

#ifdef _WIN32
#include <conio.h>
#endif

#include <iostream>
#include <sstream>
#include <cstdlib>
#include "AdventureUI.h"

#ifdef _WIN32
class ConioUI : public AdventureUI {
public:
    ConioUI() : AdventureUI() {}

    virtual char getInput() override {
        return _getch();
    }
};
#endif

// Lesson: Adapting cout/cin as the fallback
class 
    CoutCinUI : public AdventureUI {
public:
    CoutCinUI() : AdventureUI() {}
    virtual char getInput() override {
        char c;
        std::cin >> c;
        return c;
    }
};

class UIFactory {
public:
    static std::unique_ptr<AdventureUI> createUI() {
#ifdef _WIN32
        return std::make_unique<ConioUI>();
#else
        return std::make_unique<CoutCinUI>();
#endif
    }
};