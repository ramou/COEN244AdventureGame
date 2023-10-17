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
    ConioUI(std::stringstream& messages) : AdventureUI(messages) {}

    virtual char getInput() override {
        return _getch();
    }
};
#endif

// Lesson: Adapting cout/cin as the fallback
class 
    CoutCinUI : public AdventureUI {
public:
    CoutCinUI(std::stringstream& messages) : AdventureUI(messages) {}
    virtual char getInput() override {
        char c;
        std::cin >> c;
        return c;
    }
};

class UIFactory {
public:
    static std::unique_ptr<AdventureUI> createUI(std::stringstream& messages) {
#ifdef _WIN32
        return std::make_unique<ConioUI>(messages);
#else
        return std::make_unique<CoutCinUI>(messages);
#endif
    }
};