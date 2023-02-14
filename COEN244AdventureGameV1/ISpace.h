#pragma once
class ISpace
{
public:
	virtual ISpace& move(ISpace& origin) = 0;
	virtual ISpace& makeMove(char m) = 0;
	virtual void draw() = 0;

	virtual void setNorth(ISpace& s) {}
	virtual void setSouth(ISpace& s) {}
	virtual void setEast(ISpace& s) {}
	virtual void setWest(ISpace& s) {}

};

