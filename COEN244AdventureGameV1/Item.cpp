#include "Item.h"

using namespace std;

/*

We read in from the item file. The first line has the name.
The second line has the description as one line.
The rest is the ascii art.

*/

Item::Item(string itemfile) {
	ifstream itemF;
	itemF.open(itemfile);
	getline(itemF, name);
	getline(itemF, description);
	string buffer;
	stringstream streamBuffer;
	while (!itemF.eof()) {
		getline(itemF, buffer);
		//Don't copy comments. I want
		//to credit folks without putting that
		//in the game
		if (buffer[0] == '#') continue;
		streamBuffer << buffer << endl;
	}

	art = streamBuffer.str();
	itemF.close();

}