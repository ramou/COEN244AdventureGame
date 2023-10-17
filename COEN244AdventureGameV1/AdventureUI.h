#pragma once
#include <iostream>
#include <sstream>
#include "Screen.h"

class AdventureUI {
public:
	AdventureUI(std::stringstream& messages) : messages(messages) {}
    virtual void draw(Screen& screen) {
        system("CLS");
        for (int i = 0; i < screen.getLineNumber(); ++i) {
            std::cout << screen.line(i) << std::endl;
        }

        std::cout << getMessages().str();

        getMessages().str("");

    }
	virtual char getInput() = 0;
    std::stringstream& getMessages() {
        return messages;
    }
private:
	std::stringstream& messages;

};



