#pragma once

#include <string>

//It's an interface
class Screen {
public:

	virtual std::string line(int lineNumber) = 0;
	virtual int numberOfLines() = 0;
	virtual std::stringstream& messages() = 0;

};

