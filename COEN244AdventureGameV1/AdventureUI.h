#pragma once
#include <iostream>
#include <sstream>
#include "Screen.h"

class AdventureUI {
public:
	AdventureUI() {}
    virtual void draw(Screen& screen) {
        system("CLS");
        for (int i = 0; i < screen.numberOfLines(); ++i) {
            std::cout << screen.line(i) << std::endl;
        }


        std::cout << screen.messages().str();

        screen.messages().str("");

    }
	virtual char getInput() = 0;


private:


};



