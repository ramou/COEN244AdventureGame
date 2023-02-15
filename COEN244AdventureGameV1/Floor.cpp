#include "ISpace.h"

ISpace& Floor::makeMove(char m) {
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