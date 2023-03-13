#include "ISpace.h"

ISpace& Floor::makeMove(char m) {
	try {
		switch (m) {
		case 'n':
			return north->move(*this);

		case 's':
			return south->move(*this);

		case 'w':
			return west->move(*this);

		case 'e':
			return east->move(*this);

		}
		return east->move(*this);
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