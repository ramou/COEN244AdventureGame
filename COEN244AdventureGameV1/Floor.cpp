#include "ISpace.h"

ISpace& Floor::makeMove(char m) {
	try {
		switch (m) {
		case 'n':
			return north->move();

		case 's':
			return south->move();

		case 'w':
			return west->move();

		case 'e':
			return east->move();

		}
		return east->move();
	}
	catch (WalkedIntoWallException e) {
		/*An exception happened while trying
		to move. Lets add the direction we
		were moving as context and rethrow it.
		*/
		e.setDirection(m);
		throw e;
	}

}