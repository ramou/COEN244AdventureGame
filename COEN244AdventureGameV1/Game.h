#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "Level.h"
#include "Item.h"
class Game
{
public:
	Game() {
		using namespace std;
		ifstream itemConfig("items.txt");
		string buffer;
		//count how many items we'll have
		++itemCount;
		getline(itemConfig, buffer);

		while (!itemConfig.eof()) {
			++itemCount;
			getline(itemConfig, buffer);
		}

		cout << itemCount << endl;

		//dynamically allocate space for pointers to those items
		//The old way
		//allItems = (Item**)malloc(sizeof(Item*) * itemCount);
		//The new way
		allItems = new Item * [itemCount];

		cout << "We made " << itemCount << " items. " << endl;


		//Dynamically instantiate each item from the file
		itemConfig.close();
		itemConfig.open("items.txt");

		/*
		* We actually know how many lines there are, maybe we should simplify?
		int current = 0;
		while (int i = 0; i < itemCount; ++i) {
			getline(itemConfig, buffer);
			allItems[i] = new Item(buffer);
			current++;
		}
		*/

		for (int i = 0; i < itemCount; ++i) {
			getline(itemConfig, buffer);
			allItems[i] = new Item(buffer);
		}

		//This is just to make sure we actually have the items
		//We should get rid of this and instead expose
		//the items via the interface of games and let whomever
		//is using the games do this?
		for (int i = 0; i < itemCount; ++i) {
			cout << allItems[i]->getArt() << endl << allItems[i]->getName() << endl
				<< allItems[i]->getDescription() << endl;
		}

	}

	~Game() {
		for (int i = 0; i < itemCount; ++i) {
			delete allItems[i];
		}
		delete[] allItems;
	}


private:
	std::vector<Level> levels;


	Item **allItems;
	int itemCount = 0;;

};

