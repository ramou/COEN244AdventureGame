#pragma once
#include <string>
#include <fstream>
#include <sstream>

class Item {
public:


	Item(std::string itemfile);

	std::string getArt() { return art; }
	std::string getName() { return name; }
	std::string getDescription() { return description; }

private:
	std::string art;
	std::string name;
	std::string description;


};

